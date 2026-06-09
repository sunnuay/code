package main

import "flag"

func main() {
	configPath := flag.String("f", "config.yaml", "config path")
	flag.Parse()

	cfg := LoadConfig(*configPath)
	go StartWebAPI(cfg, *configPath)

	var certManager *CertManager
	if cfg.Cert.Enabled {
		certManager = StartCertManager(cfg.Cert)
	}

	if cfg.DDNS.Enabled {
		go StartDDNS(cfg.DDNS)
	}

	if cfg.Reverse.Enabled {
		go StartReverseProxy(cfg.Reverse, certManager)
	}

	if cfg.Forward.Enabled {
		go StartForwardProxy(cfg.Forward)
	}

	select {}
}
