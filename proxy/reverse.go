package main

import (
	"log"
	"net/http"
	"net/http/httputil"
	"net/url"
)

func StartReverse(cfg ReverseConfig) {
	mux := http.NewServeMux()

	for _, route := range cfg.Routes {
		targetURL, err := url.Parse(route.Target)
		if err != nil {
			log.Fatalf("Reverse: Invalid target URL for path %s: %v", route.Path, err)
		}

		proxy := httputil.NewSingleHostReverseProxy(targetURL)

		mux.Handle(route.Path, proxy)
		log.Printf("Reverse: Route %s -> %s", route.Path, route.Target)
	}

	server := &http.Server{
		Addr:    cfg.Listen,
		Handler: mux,
	}

	log.Printf("Reverse: Starting on %s", cfg.Listen)
	if err := server.ListenAndServe(); err != nil {
		log.Fatalf("Reverse: Failed to listen: %v", err)
	}
}
