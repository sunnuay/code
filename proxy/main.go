package main

import (
	"log"
)

func main() {
	cfg, err := LoadConfig("config.yaml")
	if err != nil {
		log.Fatalf("Failed to load config: %v", err)
	}

	if cfg.DDNS.Enabled {
		go StartDDNS(cfg.DDNS)
	}

	var certManager *CertManager
	if cfg.Cert.Enabled {
		certManager = StartCertManager(cfg.Cert)
	}

	if cfg.Forward.Enabled {
		go StartForwardProxy(cfg.Forward)
	}

	if cfg.Reverse.Enabled {
		go StartReverseProxy(cfg.Reverse, certManager)
	}

	select {}
}
