package main

import (
	"fmt"
	"log"
	"net/http"
	"net/http/httputil"
	"net/url"
	"os"

	"gopkg.in/yaml.v3"
)

type Config struct {
	Listen int `yaml:"listen"`
}

func main() {
	data, err := os.ReadFile("proxy/config.yaml")
	if err != nil {
		log.Fatal(err)
	}
	var cfg Config
	if err := yaml.Unmarshal(data, &cfg); err != nil {
		log.Fatal(err)
	}
	targetURL := "http://www.example.com"
	target, err := url.Parse(targetURL)
	if err != nil {
		log.Fatal(err)
	}
	proxy := &httputil.ReverseProxy{
		Rewrite: func(pr *httputil.ProxyRequest) {
			pr.SetURL(target)
		},
	}
	addr := ":" + fmt.Sprint(cfg.Listen)
	if err := http.ListenAndServe(addr, proxy); err != nil {
		log.Fatal(err)
	}
}
