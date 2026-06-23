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
		proxy, err := newProxy(route)
		if err != nil {
			log.Fatalf("Reverse: Failed to create proxy: %v", err)
		}
		mux.Handle(route.Path, proxy)
	}

	log.Printf("Reverse: Listening on %s", config.Listen)
	if err := http.ListenAndServe(config.Listen, mux); err != nil {
		log.Fatalf("Reverse: Failed to listen: %v", err)
	}
}

func newProxy(route RouteConfig) (http.Handler, error) {
	target, err := url.Parse(route.Target)
	if err != nil {
		return nil, err
	}

	proxy := &httputil.ReverseProxy{
		Rewrite: func(r *httputil.ProxyRequest) {
			r.SetURL(target)
			r.SetXForwarded()
		},
	}

	return http.StripPrefix(route.Path, proxy), nil
}
