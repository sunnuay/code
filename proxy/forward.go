package main

import (
	"io"
	"log"
	"net"
	"net/http"
	"time"
)

type ForwardProxy struct{}

func (p *ForwardProxy) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	if req.Method == http.MethodConnect {
		p.handleTunneling(w, req)
	} else {
		p.handleHTTP(w, req)
	}
}

func (p *ForwardProxy) handleTunneling(w http.ResponseWriter, r *http.Request) {
	destConn, err := net.DialTimeout("tcp", r.Host, 10*time.Second)
	if err != nil {
		http.Error(w, err.Error(), http.StatusServiceUnavailable)
		return
	}

	w.WriteHeader(http.StatusOK)

	hijacker, ok := w.(http.Hijacker)
	if !ok {
		http.Error(w, "Hijacking not supported", http.StatusInternalServerError)
		_ = destConn.Close()
		return
	}

	clientConn, _, err := hijacker.Hijack()
	if err != nil {
		http.Error(w, err.Error(), http.StatusServiceUnavailable)
		_ = destConn.Close()
		return
	}

	go func() {
		_, _ = io.Copy(destConn, clientConn)
		_ = destConn.Close()
		_ = clientConn.Close()
	}()

	go func() {
		_, _ = io.Copy(clientConn, destConn)
		_ = destConn.Close()
		_ = clientConn.Close()
	}()
}

func (p *ForwardProxy) handleHTTP(w http.ResponseWriter, req *http.Request) {
	req.RequestURI = ""

	resp, err := http.DefaultTransport.RoundTrip(req)
	if err != nil {
		http.Error(w, err.Error(), http.StatusServiceUnavailable)
		return
	}

	defer func() {
		_ = resp.Body.Close()
	}()

	for k, vv := range resp.Header {
		for _, v := range vv {
			w.Header().Add(k, v)
		}
	}
	w.WriteHeader(resp.StatusCode)

	if _, err := io.Copy(w, resp.Body); err != nil {
		log.Printf("Forward HTTP copy error: %v", err)
	}
}

func StartForwardProxy(cfg ForwardConfig) {
	server := &http.Server{
		Addr:    cfg.Listen,
		Handler: &ForwardProxy{},
	}
	log.Printf("Starting Forward Proxy on %s", cfg.Listen)
	if err := server.ListenAndServe(); err != nil {
		log.Fatalf("Forward proxy error: %v", err)
	}
}
