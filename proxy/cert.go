package main

import (
	"bytes"
	"context"
	"crypto/ecdsa"
	"crypto/elliptic"
	"crypto/rand"
	"crypto/tls"
	"crypto/x509"
	"crypto/x509/pkix"
	"encoding/pem"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"strings"
	"sync/atomic"
	"time"

	"github.com/cloudflare/cloudflare-go"
	"golang.org/x/crypto/acme"
)

var certCache atomic.Pointer[tls.Certificate]

func StartCert(config CertConfig) {
	if err := os.MkdirAll(config.CacheDir, 0o755); err != nil {
		log.Fatalf("Cert: Failed to create cache dir: %v", err)
	}

	api, err := cloudflare.NewWithAPIToken(config.APIToken)
	if err != nil {
		log.Fatalf("Cert: Failed to initialize API: %v", err)
	}

	zoneID := lookupCertZone(api, config.Domain)

	log.Printf("Cert: Starting service for domain: %s", config.Domain)

	renewCert(api, config, zoneID)

	ticker := time.NewTicker(24 * time.Hour)
	for range ticker.C {
		renewCert(api, config, zoneID)
	}
}

func GetCertificate(hello *tls.ClientHelloInfo) (*tls.Certificate, error) {
	if c := certCache.Load(); c != nil {
		return c, nil
	}
	return nil, fmt.Errorf("certificate not ready")
}

func lookupCertZone(api *cloudflare.API, domain string) *cloudflare.ResourceContainer {
	parts := strings.Split(domain, ".")
	for i := range parts {
		candidate := strings.Join(parts[i:], ".")
		id, err := api.ZoneIDByName(candidate)
		if err == nil && id != "" {
			return cloudflare.ZoneIdentifier(id)
		}
	}
	log.Fatalf("Cert: Failed to find ZoneID for domain: %s", domain)
	return nil
}

func renewCert(api *cloudflare.API, config CertConfig, zoneID *cloudflare.ResourceContainer) {
	certPath := filepath.Join(config.CacheDir, "cert.pem")
	keyPath := filepath.Join(config.CacheDir, "key.pem")

	if c, err := tls.LoadX509KeyPair(certPath, keyPath); err == nil {
		if x509Cert, err := x509.ParseCertificate(c.Certificate[0]); err == nil {
			if time.Until(x509Cert.NotAfter) > 30*24*time.Hour {
				certCache.Store(&c)
				log.Printf("Cert: Loaded from cache, expires: %s", x509Cert.NotAfter.Format(time.RFC3339))
				return
			}
		}
	}

	log.Printf("Cert: Obtaining certificate for %s...", config.Domain)

	c, err := obtainCert(api, config, zoneID)
	if err != nil {
		log.Printf("Cert: Obtain failed: %v", err)
		return
	}

	certCache.Store(c)
	log.Printf("Cert: Successfully obtained for %s", config.Domain)
}

func obtainCert(api *cloudflare.API, config CertConfig, zoneID *cloudflare.ResourceContainer) (*tls.Certificate, error) {
	ctx := context.Background()

	accountKey, err := ecdsa.GenerateKey(elliptic.P256(), rand.Reader)
	if err != nil {
		return nil, err
	}

	client := &acme.Client{
		Key:          accountKey,
		DirectoryURL: acme.LetsEncryptURL,
	}

	_, err = client.Register(ctx, &acme.Account{Contact: []string{"mailto:" + config.Email}}, acme.AcceptTOS)
	if err != nil && err != acme.ErrAccountAlreadyExists {
		return nil, err
	}

	order, err := client.AuthorizeOrder(ctx, acme.DomainIDs(config.Domain))
	if err != nil {
		return nil, err
	}

	dnsChallenge, authURL := findDNSChallenge(client, ctx, order)
	if dnsChallenge == nil {
		return nil, fmt.Errorf("no dns-01 challenge found")
	}

	txtValue, err := client.DNS01ChallengeRecord(dnsChallenge.Token)
	if err != nil {
		return nil, err
	}

	recordID, err := upsertCertTXT(api, zoneID, config.Domain, txtValue)
	if err != nil {
		return nil, err
	}
	defer deleteCertTXT(api, zoneID, recordID)

	log.Printf("Cert: Waiting 30s for DNS propagation...")
	time.Sleep(30 * time.Second)

	if _, err := client.Accept(ctx, dnsChallenge); err != nil {
		return nil, err
	}
	if _, err := client.WaitAuthorization(ctx, authURL); err != nil {
		return nil, err
	}

	return generateCert(client, ctx, config, order)
}

func findDNSChallenge(client *acme.Client, ctx context.Context, order *acme.Order) (*acme.Challenge, string) {
	for _, uri := range order.AuthzURLs {
		auth, err := client.GetAuthorization(ctx, uri)
		if err != nil {
			continue
		}
		for _, chal := range auth.Challenges {
			if chal.Type == "dns-01" {
				return chal, uri
			}
		}
	}
	return nil, ""
}

func generateCert(client *acme.Client, ctx context.Context, config CertConfig, order *acme.Order) (*tls.Certificate, error) {
	certKey, err := ecdsa.GenerateKey(elliptic.P256(), rand.Reader)
	if err != nil {
		return nil, err
	}
	csr, err := x509.CreateCertificateRequest(rand.Reader, &x509.CertificateRequest{
		Subject: pkix.Name{CommonName: config.Domain}, DNSNames: []string{config.Domain},
	}, certKey)
	if err != nil {
		return nil, err
	}

	derCerts, _, err := client.CreateOrderCert(ctx, order.FinalizeURL, csr, true)
	if err != nil {
		return nil, err
	}

	var certPEM bytes.Buffer
	for _, b := range derCerts {
		pem.Encode(&certPEM, &pem.Block{Type: "CERTIFICATE", Bytes: b})
	}

	keyBytes, err := x509.MarshalECPrivateKey(certKey)
	if err != nil {
		return nil, err
	}
	var keyPEM bytes.Buffer
	pem.Encode(&keyPEM, &pem.Block{Type: "EC PRIVATE KEY", Bytes: keyBytes})

	os.WriteFile(filepath.Join(config.CacheDir, "cert.pem"), certPEM.Bytes(), 0o644)
	os.WriteFile(filepath.Join(config.CacheDir, "key.pem"), keyPEM.Bytes(), 0o600)

	tlsCert, err := tls.X509KeyPair(certPEM.Bytes(), keyPEM.Bytes())
	return &tlsCert, err
}

func upsertCertTXT(api *cloudflare.API, zoneID *cloudflare.ResourceContainer, domain, txtValue string) (string, error) {
	ctx := context.Background()
	name := "_acme-challenge." + domain

	rec, err := api.CreateDNSRecord(ctx, zoneID, cloudflare.CreateDNSRecordParams{
		Type: "TXT", Name: name, Content: txtValue, TTL: 60,
	})
	if err != nil {
		return "", err
	}
	log.Printf("Cert: Created TXT record: %s", name)
	return rec.ID, nil
}

func deleteCertTXT(api *cloudflare.API, zoneID *cloudflare.ResourceContainer, recordID string) {
	if recordID == "" {
		return
	}
	if err := api.DeleteDNSRecord(context.Background(), zoneID, recordID); err != nil {
		log.Printf("Cert: Failed to delete TXT record: %v", err)
	} else {
		log.Printf("Cert: Deleted TXT record")
	}
}
