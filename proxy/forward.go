package main

import (
	"io"
	"log"
	"net"
	"net/http"
	"time"
)

type Forward struct{}

func (p *Forward) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	if req.Method == http.MethodConnect {
		p.handleTunneling(w, req)
	} else {
		p.handleHTTP(w, req)
	}
}

func (p *Forward) handleTunneling(w http.ResponseWriter, req *http.Request) {
	destConn, err := net.DialTimeout("tcp", req.Host, 10*time.Second)
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
	}()

	go func() {
		_, _ = io.Copy(clientConn, destConn)
		_ = clientConn.Close()
	}()
}

func (p *Forward) handleHTTP(w http.ResponseWriter, req *http.Request) {
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
		log.Printf("Forward: HTTP copy error: %v", err)
	}
}

func StartForward(cfg ForwardConfig) {
	server := &http.Server{
		Addr:    cfg.Listen,
		Handler: &Forward{},
	}
	log.Printf("Forward: Starting on %s", cfg.Listen)
	if err := server.ListenAndServe(); err != nil {
		log.Fatalf("Forward: Listen error: %v", err)
	}
}
