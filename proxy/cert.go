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
	"sync"
	"time"

	"github.com/cloudflare/cloudflare-go"
	"golang.org/x/crypto/acme"
)

type CertManager struct {
	cfg  CertConfig
	cert *tls.Certificate
	mu   sync.RWMutex
}

func StartCertManager(cfg CertConfig) *CertManager {
	if err := os.MkdirAll(cfg.CacheDir, 0o755); err != nil {
		log.Fatalf("Cert: Failed to create cache dir: %v", err)
	}

	cm := &CertManager{cfg: cfg}

	cm.renew()

	go func() {
		ticker := time.NewTicker(24 * time.Hour)
		defer ticker.Stop()
		for range ticker.C {
			cm.renew()
		}
	}()

	return cm
}

func (cm *CertManager) GetCertificate(hello *tls.ClientHelloInfo) (*tls.Certificate, error) {
	cm.mu.RLock()
	defer cm.mu.RUnlock()
	if cm.cert != nil {
		return cm.cert, nil
	}
	return nil, fmt.Errorf("certificate not ready")
}

func (cm *CertManager) renew() {
	certPath := filepath.Join(cm.cfg.CacheDir, "cert.pem")
	keyPath := filepath.Join(cm.cfg.CacheDir, "key.pem")

	if cert, err := tls.LoadX509KeyPair(certPath, keyPath); err == nil {
		if x509Cert, err := x509.ParseCertificate(cert.Certificate[0]); err == nil {
			if time.Until(x509Cert.NotAfter) > 30*24*time.Hour {
				cm.mu.Lock()
				cm.cert = &cert
				cm.mu.Unlock()
				log.Printf("Cert: Valid certificate loaded from cache for %s (expires: %s)", cm.cfg.Domain, x509Cert.NotAfter.Format(time.RFC3339))
				return
			}
		}
	}

	log.Printf("Cert: Obtaining/Renewing certificate for %s via DNS-01...", cm.cfg.Domain)

	cert, err := cm.obtainCertificate()
	if err != nil {
		log.Printf("Cert: Failed to obtain certificate: %v", err)
		return
	}

	cm.mu.Lock()
	cm.cert = cert
	cm.mu.Unlock()
	log.Printf("Cert: Successfully applied and loaded new certificate for %s", cm.cfg.Domain)
}

func (cm *CertManager) obtainCertificate() (*tls.Certificate, error) {
	ctx := context.Background()

	accountKey, err := ecdsa.GenerateKey(elliptic.P256(), rand.Reader)
	if err != nil {
		return nil, err
	}

	client := &acme.Client{
		Key:          accountKey,
		DirectoryURL: acme.LetsEncryptURL,
	}

	_, err = client.Register(ctx, &acme.Account{Contact: []string{"mailto:" + cm.cfg.Email}}, acme.AcceptTOS)
	if err != nil && err != acme.ErrAccountAlreadyExists {
		return nil, fmt.Errorf("account registration failed: %v", err)
	}

	order, err := client.AuthorizeOrder(ctx, acme.DomainIDs(cm.cfg.Domain))
	if err != nil {
		return nil, fmt.Errorf("authorize order failed: %v", err)
	}

	var dnsChallenge *acme.Challenge
	var authzURL string

	for _, authzURI := range order.AuthzURLs {
		authz, err := client.GetAuthorization(ctx, authzURI)
		if err != nil {
			continue
		}
		for _, chal := range authz.Challenges {
			if chal.Type == "dns-01" {
				dnsChallenge = chal
				authzURL = authzURI
				break
			}
		}
	}

	if dnsChallenge == nil {
		return nil, fmt.Errorf("no dns-01 challenge found")
	}

	txtValue, err := client.DNS01ChallengeRecord(dnsChallenge.Token)
	if err != nil {
		return nil, err
	}

	recordID, err := cm.setupCloudflareTXT(txtValue)
	if err != nil {
		return nil, fmt.Errorf("cloudflare setup failed: %v", err)
	}
	defer cm.cleanupCloudflareTXT(recordID)

	log.Printf("Cert: Waiting 30 seconds for DNS propagation...")
	time.Sleep(30 * time.Second)

	if _, err := client.Accept(ctx, dnsChallenge); err != nil {
		return nil, fmt.Errorf("challenge accept failed: %v", err)
	}

	if _, err := client.WaitAuthorization(ctx, authzURL); err != nil {
		return nil, fmt.Errorf("wait authorization failed: %v", err)
	}

	certKey, err := ecdsa.GenerateKey(elliptic.P256(), rand.Reader)
	if err != nil {
		return nil, err
	}
	csrReq := &x509.CertificateRequest{
		Subject:  pkix.Name{CommonName: cm.cfg.Domain},
		DNSNames: []string{cm.cfg.Domain},
	}
	csr, err := x509.CreateCertificateRequest(rand.Reader, csrReq, certKey)
	if err != nil {
		return nil, err
	}

	derCerts, _, err := client.CreateOrderCert(ctx, order.FinalizeURL, csr, true)
	if err != nil {
		return nil, fmt.Errorf("create order cert failed: %v", err)
	}

	var certPEM bytes.Buffer
	for _, b := range derCerts {
		if err := pem.Encode(&certPEM, &pem.Block{Type: "CERTIFICATE", Bytes: b}); err != nil {
			return nil, fmt.Errorf("failed to encode certificate: %v", err)
		}
	}

	keyBytes, err := x509.MarshalECPrivateKey(certKey)
	if err != nil {
		return nil, err
	}

	var keyPEM bytes.Buffer
	if err := pem.Encode(&keyPEM, &pem.Block{Type: "EC PRIVATE KEY", Bytes: keyBytes}); err != nil {
		return nil, fmt.Errorf("failed to encode private key: %v", err)
	}

	if err := os.WriteFile(filepath.Join(cm.cfg.CacheDir, "cert.pem"), certPEM.Bytes(), 0o644); err != nil {
		return nil, fmt.Errorf("failed to write cert.pem to cache: %v", err)
	}
	if err := os.WriteFile(filepath.Join(cm.cfg.CacheDir, "key.pem"), keyPEM.Bytes(), 0o600); err != nil {
		return nil, fmt.Errorf("failed to write key.pem to cache: %v", err)
	}

	tlsCert, err := tls.X509KeyPair(certPEM.Bytes(), keyPEM.Bytes())
	return &tlsCert, err
}

func (cm *CertManager) setupCloudflareTXT(txtValue string) (string, error) {
	api, err := cloudflare.NewWithAPIToken(cm.cfg.APIToken)
	if err != nil {
		return "", err
	}
	ctx := context.Background()
	zoneID := cloudflare.ZoneIdentifier(cm.cfg.ZoneID)
	recordName := "_acme-challenge." + cm.cfg.Domain

	rec, err := api.CreateDNSRecord(ctx, zoneID, cloudflare.CreateDNSRecordParams{
		Type:    "TXT",
		Name:    recordName,
		Content: txtValue,
		TTL:     60,
	})
	if err != nil {
		return "", err
	}
	log.Printf("Cert: Created Cloudflare TXT record for %s", recordName)
	return rec.ID, nil
}

func (cm *CertManager) cleanupCloudflareTXT(recordID string) {
	if recordID == "" {
		return
	}
	api, err := cloudflare.NewWithAPIToken(cm.cfg.APIToken)
	if err == nil {
		err := api.DeleteDNSRecord(context.Background(), cloudflare.ZoneIdentifier(cm.cfg.ZoneID), recordID)
		if err != nil {
			log.Printf("Cert: Failed to clean up Cloudflare TXT record: %v", err)
		} else {
			log.Printf("Cert: Cleaned up Cloudflare TXT record")
		}
	}
}
