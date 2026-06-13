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

	zoneID, err := getDDNSZoneID(api, config.Domain)
	if err != nil {
		log.Fatalf("DDNS: Failed to find ZoneID: %v", err)
	}

	log.Printf("DDNS: Starting service for domain: %s", config.Domain)

	var lastIP string
	ticker := time.NewTicker(time.Duration(config.Interval) * time.Second)
	defer ticker.Stop()

	for {
		if ip := getPublicIPv6(); ip != "" && ip != lastIP {
			if upsertDNSRecord(api, zoneID, config.Domain, ip) {
				lastIP = ip
			}
		}
		<-ticker.C
	}
}

func getDDNSZoneID(api *cloudflare.API, domain string) (*cloudflare.ResourceContainer, error) {
	parts := strings.Split(domain, ".")
	var lastErr error
	for i := range parts {
		candidate := strings.Join(parts[i:], ".")
		id, err := api.ZoneIDByName(candidate)
		if err == nil && id != "" {
			return cloudflare.ZoneIdentifier(id), nil
		}
		lastErr = err
	}
	return nil, lastErr
}

func getPublicIPv6() string {
	ifaces, err := net.Interfaces()
	if err != nil {
		return ""
	}
	for _, iface := range ifaces {
		if !isUp(iface) || isSkipped(iface.Name) {
			continue
		}
		if ip := findGlobalIPv6(iface); ip != "" {
			log.Printf("DDNS: Found IPv6 %s on interface %s", ip, iface.Name)
			return ip
		}
	}
	return ""
}

func isUp(iface net.Interface) bool {
	return iface.Flags&net.FlagUp != 0 && iface.Flags&net.FlagLoopback == 0
}

var skippedPrefixes = []string{"docker", "br-", "veth", "virbr", "wg", "tailscale"}

func isSkipped(name string) bool {
	for _, prefix := range skippedPrefixes {
		if strings.HasPrefix(name, prefix) {
			return true
		}
	}
	return false
}

func findGlobalIPv6(iface net.Interface) string {
	addrs, _ := iface.Addrs()
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
		log.Printf("DDNS: Record already exists for %s -> %s", domain, ip)
		return true
	}

	proxied := false
	var actionErr error
	if len(records) == 0 {
		_, actionErr = api.CreateDNSRecord(ctx, zoneID, cloudflare.CreateDNSRecordParams{
			Type: "AAAA", Name: domain, Content: ip, Proxied: &proxied, TTL: 1,
		})
	} else {
		_, actionErr = api.UpdateDNSRecord(ctx, zoneID, cloudflare.UpdateDNSRecordParams{
			ID: records[0].ID, Type: "AAAA", Name: domain, Content: ip, Proxied: &proxied, TTL: 1,
		})
	}

	if actionErr != nil {
		log.Printf("DDNS: Update failed: %v", actionErr)
		return false
	}
	log.Printf("DDNS: Success %s -> %s", domain, ip)
	return true
}
