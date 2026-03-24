package main

import (
	"crypto/tls"
	"log"
	"net/http"
	"net/http/httputil"
	"net/url"
)

func StartReverseProxy(cfg ReverseConfig, cm *CertManager) {
	mux := http.NewServeMux()

	for _, route := range cfg.Routes {
		targetURL, err := url.Parse(route.Target)
		if err != nil {
			log.Fatalf("Invalid target URL for path %s: %v", route.Path, err)
		}

		proxy := httputil.NewSingleHostReverseProxy(targetURL)

		mux.Handle(route.Path, proxy)
		log.Printf("Reverse Proxy Route: %s -> %s", route.Path, route.Target)
	}

	server := &http.Server{
		Addr:    cfg.Listen,
		Handler: mux,
	}

	if cm != nil {
		server.TLSConfig = &tls.Config{
			GetCertificate: cm.GetCertificate,
		}
		log.Printf("Starting Reverse Proxy (HTTPS) on %s", cfg.Listen)
		if err := server.ListenAndServeTLS("", ""); err != nil {
			log.Fatalf("Reverse proxy TLS error: %v", err)
		}
	} else {
		log.Printf("Starting Reverse Proxy (HTTP) on %s", cfg.Listen)
		if err := server.ListenAndServe(); err != nil {
			log.Fatalf("Reverse proxy error: %v", err)
		}
	}
}
