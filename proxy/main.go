package main

import "flag"

func main() {
	configPath := flag.String("f", "config.yaml", "config path")
	flag.Parse()

	config := LoadConfig(*configPath)

	go StartAPI(config, *configPath)

	if config.Cert.Enabled {
		go StartCert(config.Cert)
	}

	if config.DDNS.Enabled {
		go StartDDNS(config.DDNS)
	}

	if config.Reverse.Enabled {
		go StartReverse(config.Reverse)
	}

	if config.Forward.Enabled {
		go StartForward(config.Forward)
	}

	select {}
}
