package main

import (
	"log"
)

func main() {
	cfg, err := LoadConfig("proxy/config.yaml")
	if err != nil {
		log.Fatalf("Failed to load config: %v", err)
	}

	if cfg.Forward.Enabled {
		go StartForwardProxy(cfg.Forward)
	}

	if cfg.Reverse.Enabled {
		go StartReverseProxy(cfg.Reverse)
	}

	if cfg.DDNS.Enabled {
		go StartDDNS(cfg.DDNS)
	}

	select {}
}
