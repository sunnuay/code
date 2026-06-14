package main

import "flag"

func main() {
	var filename string
	flag.StringVar(&filename, "f", "config.yaml", "")
	flag.Parse()

	config := LoadConfig(filename)

	if config.Forward.Enabled {
		go StartForward(config.Forward)
	}

	if config.Reverse.Enabled {
		go StartReverse(config.Reverse)
	}

	if config.DDNS.Enabled {
		go StartDDNS(config.DDNS)
	}

	if config.Cert.Enabled {
		go StartCert(config.Cert)
	}

	StartAPI(config, filename)
}
