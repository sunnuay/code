package main

import (
	"context"
	"log"
	"net"
	"strings"
	"time"

	"github.com/cloudflare/cloudflare-go"
)

func StartDDNS(config DDNSConfig) {
	api, err := cloudflare.NewWithAPIToken(config.APIToken)
	if err != nil {
		log.Fatalf("DDNS: Failed to initialize API: %v", err)
	}

	parts := strings.Split(config.Domain, ".")
	var zoneID *cloudflare.ResourceContainer
	for i := range parts {
		candidate := strings.Join(parts[i:], ".")
		id, err := api.ZoneIDByName(candidate)
		if err == nil && id != "" {
			zoneID = cloudflare.ZoneIdentifier(id)
			break
		}
	}
	if zoneID == nil {
		log.Fatalf("DDNS: Failed to find ZoneID for domain: %s", config.Domain)
	}

	log.Printf("DDNS: Starting service for domain: %s", config.Domain)

	ticker := time.NewTicker(time.Duration(config.Interval) * time.Second)
	var lastIP string
	for {
		if ip := getPublicIPv6(); ip != "" && ip != lastIP {
			if upsertDNSRecord(api, zoneID, config.Domain, ip) {
				lastIP = ip
			}
		}
		<-ticker.C
	}
}

func getPublicIPv6() string {
	addrs, err := net.InterfaceAddrs()
	if err != nil {
		return ""
	}

	for _, addr := range addrs {
		ipnet, ok := addr.(*net.IPNet)
		if !ok {
			continue
		}
		if ip := ipnet.IP; ip.To4() == nil && ip.IsGlobalUnicast() {
			return ip.String()
		}
	}
	return ""
}

func upsertDNSRecord(api *cloudflare.API, zoneID *cloudflare.ResourceContainer, domain, ip string) bool {
	ctx := context.Background()
	records, _, err := api.ListDNSRecords(ctx, zoneID, cloudflare.ListDNSRecordsParams{
		Type: "AAAA", Name: domain,
	})
	if err != nil {
		log.Printf("DDNS: Query failed: %v", err)
		return false
	}

	if len(records) > 0 && records[0].Content == ip {
		log.Printf("DDNS: No update needed: %s -> %s", domain, ip)
		return true
	}

	proxied := false
	if len(records) == 0 {
		_, err = api.CreateDNSRecord(ctx, zoneID, cloudflare.CreateDNSRecordParams{
			Type: "AAAA", Name: domain, Content: ip, Proxied: &proxied, TTL: 1,
		})
	} else {
		_, err = api.UpdateDNSRecord(ctx, zoneID, cloudflare.UpdateDNSRecordParams{
			ID: records[0].ID, Type: "AAAA", Name: domain, Content: ip, Proxied: &proxied, TTL: 1,
		})
	}
	if err != nil {
		log.Printf("DDNS: Update failed: %v", err)
		return false
	}
	log.Printf("DDNS: Success %s -> %s", domain, ip)
	return true
}
