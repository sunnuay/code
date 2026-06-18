package main

import (
	"io"
	"log"
	"net"
	"net/http"
	"time"
)

func StartForward(config ForwardConfig) {
	log.Printf("Forward: Listening on %s", config.Listen)
	if err := http.ListenAndServe(config.Listen, http.HandlerFunc(proxyHandler)); err != nil {
		log.Fatalf("Forward: Failed to listen: %v", err)
	}
}

func proxyHandler(w http.ResponseWriter, req *http.Request) {
	if req.Method == http.MethodConnect {
		handleTunneling(w, req)
	} else {
		handleHTTP(w, req)
	}
}

func handleTunneling(w http.ResponseWriter, req *http.Request) {
	destConn, err := net.DialTimeout("tcp", req.Host, 10*time.Second)
	if err != nil {
		http.Error(w, err.Error(), http.StatusServiceUnavailable)
		return
	}

	hijacker, ok := w.(http.Hijacker)
	if !ok {
		destConn.Close()
		http.Error(w, "Hijacking not supported", http.StatusInternalServerError)
		return
	}

	clientConn, _, err := hijacker.Hijack()
	if err != nil {
		destConn.Close()
		http.Error(w, err.Error(), http.StatusServiceUnavailable)
		return
	}

	clientConn.Write([]byte("HTTP/1.1 200 Connection Established\r\n\r\n"))

	go func() {
		io.Copy(destConn, clientConn)
		destConn.Close()
	}()

	io.Copy(clientConn, destConn)
	clientConn.Close()
}

func handleHTTP(w http.ResponseWriter, req *http.Request) {
	req.RequestURI = ""

	resp, err := http.DefaultTransport.RoundTrip(req)
	if err != nil {
		http.Error(w, err.Error(), http.StatusServiceUnavailable)
		return
	}
	defer resp.Body.Close()

	for k, vv := range resp.Header {
		for _, v := range vv {
			w.Header().Add(k, v)
		}
	}
	w.WriteHeader(resp.StatusCode)

	io.Copy(w, resp.Body)
}
