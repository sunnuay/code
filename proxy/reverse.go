package main

import (
	"log"
	"net/http"
	"net/http/httputil"
	"net/url"
)

func StartReverse(config ReverseConfig) {
	mux := http.NewServeMux()

	for _, route := range config.Routes {
		target, err := url.Parse(route.Target)
		if err != nil {
			log.Fatalf("Reverse: Invalid target: %s", route.Target)
		}
		proxy := httputil.NewSingleHostReverseProxy(target)
		mux.Handle(route.Path, proxy)
	}

	log.Printf("Reverse: Listening on %s", config.Listen)
	if err := http.ListenAndServe(config.Listen, mux); err != nil {
		log.Fatalf("Reverse: Failed to listen: %v", err)
	}
}
