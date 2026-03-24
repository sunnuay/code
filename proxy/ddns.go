package main

import (
	"context"
	"io"
	"log"
	"net/http"
	"strings"
	"time"

	"github.com/cloudflare/cloudflare-go"
)

func StartDDNS(cfg DDNSConfig) {
	api, err := cloudflare.NewWithAPIToken(cfg.APIToken)
	if err != nil {
		log.Fatalf("DDNS: Failed to initialize Cloudflare client: %v", err)
	}

	log.Printf("DDNS: Starting service for domain: %s", cfg.Domain)
	updateIPv6Record(api, cfg)

	ticker := time.NewTicker(time.Duration(cfg.Interval) * time.Second)
	defer ticker.Stop()

	for range ticker.C {
		updateIPv6Record(api, cfg)
	}
}

func updateIPv6Record(api *cloudflare.API, cfg DDNSConfig) {
	currentIPv6, err := getPublicIPv6()
	if err != nil {
		log.Printf("DDNS: Failed to get local IPv6: %v", err)
		return
	}

	ctx := context.Background()
	zoneID := cloudflare.ZoneIdentifier(cfg.ZoneID)

	records, _, err := api.ListDNSRecords(ctx, zoneID, cloudflare.ListDNSRecordsParams{
		Type: "AAAA",
		Name: cfg.Domain,
	})
	if err != nil {
		log.Printf("DDNS: Failed to query DNS records: %v", err)
		return
	}

	proxied := false

	if len(records) == 0 {
		_, err = api.CreateDNSRecord(ctx, zoneID, cloudflare.CreateDNSRecordParams{
			Type:    "AAAA",
			Name:    cfg.Domain,
			Content: currentIPv6,
			Proxied: &proxied,
			TTL:     1,
		})
		if err != nil {
			log.Printf("DDNS: Failed to create DNS record: %v", err)
			return
		}
		log.Printf("DDNS: Successfully created AAAA record -> %s", currentIPv6)
		return
	}

	record := records[0]
	if record.Content == currentIPv6 {
		return
	}

	_, err = api.UpdateDNSRecord(ctx, zoneID, cloudflare.UpdateDNSRecordParams{
		ID:      record.ID,
		Type:    "AAAA",
		Name:    cfg.Domain,
		Content: currentIPv6,
		Proxied: &proxied,
		TTL:     1,
	})
	if err != nil {
		log.Printf("DDNS: Failed to update DNS record: %v", err)
		return
	}
	log.Printf("DDNS: Successfully updated AAAA record: [%s] -> [%s]", record.Content, currentIPv6)
}

func getPublicIPv6() (string, error) {
	resp, err := http.Get("https://api6.ipify.org")
	if err != nil {
		return "", err
	}
	defer func() {
		if err := resp.Body.Close(); err != nil {
			log.Printf("DDNS: Failed to close response body: %v", err)
		}
	}()

	ipBytes, err := io.ReadAll(resp.Body)
	if err != nil {
		return "", err
	}
	return strings.TrimSpace(string(ipBytes)), nil
}
