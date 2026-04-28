package main

import (
	"context"
	"log"
	"net"
	"strings"
	"time"

	"github.com/cloudflare/cloudflare-go"
)

func StartDDNS(cfg DDNSConfig) {
	api, err := cloudflare.NewWithAPIToken(cfg.APIToken)
	if err != nil {
		log.Fatalf("DDNS: Failed to initialize Cloudflare client: %v", err)
	}

	var lastKnownIPv6 string

	log.Printf("DDNS: Starting service for domain: %s", cfg.Domain)
	updateIPv6Record(api, cfg, &lastKnownIPv6)

	ticker := time.NewTicker(time.Duration(cfg.Interval) * time.Second)
	defer ticker.Stop()

	for range ticker.C {
		updateIPv6Record(api, cfg, &lastKnownIPv6)
	}
}

func updateIPv6Record(api *cloudflare.API, cfg DDNSConfig, lastKnownIPv6 *string) {
	currentIPv6, err := getPublicIPv6()
	if err != nil {
		log.Printf("DDNS: Failed to get local IPv6: %v", err)
		return
	}
	if currentIPv6 == "" {
		log.Printf("DDNS: No public IPv6 address found on any interface")
		return
	}

	if currentIPv6 == *lastKnownIPv6 {
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
		*lastKnownIPv6 = currentIPv6
		return
	}

	record := records[0]
	if record.Content == currentIPv6 {
		log.Printf("DDNS: Record already exists for %s -> %s", cfg.Domain, currentIPv6)
		*lastKnownIPv6 = currentIPv6
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
	*lastKnownIPv6 = currentIPv6
}

func getPublicIPv6() (string, error) {
	ifaces, err := net.Interfaces()
	if err != nil {
		return "", err
	}

	for _, iface := range ifaces {
		if iface.Flags&net.FlagUp == 0 || iface.Flags&net.FlagLoopback != 0 {
			continue
		}

		name := iface.Name
		if strings.HasPrefix(name, "docker") || strings.HasPrefix(name, "br-") ||
			strings.HasPrefix(name, "veth") || strings.HasPrefix(name, "virbr") ||
			strings.HasPrefix(name, "wg") || strings.HasPrefix(name, "tailscale") {
			continue
		}

		addrs, err := iface.Addrs()
		if err != nil {
			continue
		}

		for _, addr := range addrs {
			ipnet, ok := addr.(*net.IPNet)
			if !ok {
				continue
			}
			ip := ipnet.IP
			if ip.To4() != nil {
				continue
			}
			if !ip.IsGlobalUnicast() {
				continue
			}
			log.Printf("DDNS: Found IPv6 %s on interface %s", ip.String(), iface.Name)
			return ip.String(), nil
		}
	}

	return "", nil
}
