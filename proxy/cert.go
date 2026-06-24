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
	"time"

	"github.com/cloudflare/cloudflare-go"
	"golang.org/x/crypto/acme"
)

func StartCert(config CertConfig) {
	if err := os.MkdirAll(filepath.Dir(config.Cert), 0o755); err != nil {
		log.Fatalf("Cert: Failed to create cert parent dir: %v", err)
	}
	if err := os.MkdirAll(filepath.Dir(config.Key), 0o755); err != nil {
		log.Fatalf("Cert: Failed to create key parent dir: %v", err)
	}

	api, err := cloudflare.NewWithAPIToken(config.APIToken)
	if err != nil {
		log.Fatalf("Cert: Failed to initialize API: %v", err)
	}

	zoneID := lookupZoneID(api, config.Domain)
	if zoneID == nil {
		log.Fatalf("Cert: Failed to find ZoneID for domain: %s", config.Domain)
	}

	log.Printf("Cert: Starting service for domain: %s", config.Domain)

	ticker := time.NewTicker(24 * time.Hour)
	for {
		renewCert(api, config, zoneID)
		<-ticker.C
	}
}

func renewCert(api *cloudflare.API, config CertConfig, zoneID *cloudflare.ResourceContainer) {
	renewBefore := 30 * 24 * time.Hour

	if c, err := tls.LoadX509KeyPair(config.Cert, config.Key); err == nil {
		if x509Cert, err := x509.ParseCertificate(c.Certificate[0]); err == nil {
			if time.Until(x509Cert.NotAfter) > renewBefore {
				log.Printf("Cert: Loaded from config, expires: %s", x509Cert.NotAfter.Format(time.RFC3339))
				return
			}
		}
	}

	log.Printf("Cert: Obtaining certificate for %s...", config.Domain)

	if err := obtainCert(api, config, zoneID); err != nil {
		log.Printf("Cert: Obtain failed: %v", err)
		return
	}

	log.Printf("Cert: Successfully obtained for %s", config.Domain)
}

func obtainCert(api *cloudflare.API, config CertConfig, zoneID *cloudflare.ResourceContainer) error {
	ctx := context.Background()
	accountKey, err := ecdsa.GenerateKey(elliptic.P256(), rand.Reader)
	if err != nil {
		return err
	}
	client := &acme.Client{Key: accountKey, DirectoryURL: acme.LetsEncryptURL}

	_, err = client.Register(ctx, &acme.Account{}, acme.AcceptTOS)
	if err != nil {
		return err
	}
	order, err := client.AuthorizeOrder(ctx, acme.DomainIDs(config.Domain))
	if err != nil {
		return err
	}
	auth, err := client.GetAuthorization(ctx, order.AuthzURLs[0])
	if err != nil {
		return err
	}

	var dnsChallenge *acme.Challenge
	for _, chal := range auth.Challenges {
		if chal.Type == "dns-01" {
			dnsChallenge = chal
			break
		}
	}
	if dnsChallenge == nil {
		return fmt.Errorf("no dns-01 challenge found")
	}

	txtValue, err := client.DNS01ChallengeRecord(dnsChallenge.Token)
	if err != nil {
		return err
	}
	recordID, err := createCertTXT(api, zoneID, config.Domain, txtValue)
	if err != nil {
		return err
	}
	defer deleteCertTXT(api, zoneID, recordID)

	log.Printf("Cert: Waiting 30s for DNS propagation...")
	time.Sleep(30 * time.Second)

	if _, err := client.Accept(ctx, dnsChallenge); err != nil {
		return err
	}
	if _, err := client.WaitAuthorization(ctx, auth.URI); err != nil {
		return err
	}

	return generateCert(client, ctx, config, order)
}

func generateCert(client *acme.Client, ctx context.Context, config CertConfig, order *acme.Order) error {
	certKey, err := ecdsa.GenerateKey(elliptic.P256(), rand.Reader)
	if err != nil {
		return err
	}
	csr, err := x509.CreateCertificateRequest(rand.Reader, &x509.CertificateRequest{
		Subject: pkix.Name{CommonName: config.Domain}, DNSNames: []string{config.Domain},
	}, certKey)
	if err != nil {
		return err
	}

	derCerts, _, err := client.CreateOrderCert(ctx, order.FinalizeURL, csr, true)
	if err != nil {
		return err
	}

	var certPEM bytes.Buffer
	for _, b := range derCerts {
		pem.Encode(&certPEM, &pem.Block{Type: "CERTIFICATE", Bytes: b})
	}

	keyBytes, err := x509.MarshalECPrivateKey(certKey)
	if err != nil {
		return err
	}
	var keyPEM bytes.Buffer
	pem.Encode(&keyPEM, &pem.Block{Type: "EC PRIVATE KEY", Bytes: keyBytes})

	os.WriteFile(config.Cert, certPEM.Bytes(), 0o644)
	os.WriteFile(config.Key, keyPEM.Bytes(), 0o600)

	return nil
}

func createCertTXT(api *cloudflare.API, zoneID *cloudflare.ResourceContainer, domain, txtValue string) (string, error) {
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
		return
	}
	log.Printf("Cert: Deleted TXT record")
}
