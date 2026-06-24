package main

import (
	"log"
	"os"

	"gopkg.in/yaml.v3"
)

type Config struct {
	Forward ForwardConfig `yaml:"forward" json:"forward"`
	Reverse ReverseConfig `yaml:"reverse" json:"reverse"`
	DDNS    DDNSConfig    `yaml:"ddns" json:"ddns"`
	Cert    CertConfig    `yaml:"cert" json:"cert"`
	API     APIConfig     `yaml:"api" json:"api"`
}

type ForwardConfig struct {
	Enabled bool   `yaml:"enabled" json:"enabled"`
	Listen  string `yaml:"listen" json:"listen"`
}

type ReverseConfig struct {
	Enabled bool          `yaml:"enabled" json:"enabled"`
	Listen  string        `yaml:"listen" json:"listen"`
	TLS     bool          `yaml:"tls" json:"tls"`
	Cert    string        `yaml:"cert" json:"cert"`
	Key     string        `yaml:"key" json:"key"`
	Routes  []RouteConfig `yaml:"routes" json:"routes"`
}

type RouteConfig struct {
	Path   string `yaml:"path" json:"path"`
	Target string `yaml:"target" json:"target"`
}

type DDNSConfig struct {
	Enabled  bool   `yaml:"enabled" json:"enabled"`
	Interval int    `yaml:"interval" json:"interval"`
	Domain   string `yaml:"domain" json:"domain"`
	APIToken string `yaml:"api_token" json:"api_token"`
}

type CertConfig struct {
	Enabled  bool   `yaml:"enabled" json:"enabled"`
	Cert     string `yaml:"cert" json:"cert"`
	Key      string `yaml:"key" json:"key"`
	Domain   string `yaml:"domain" json:"domain"`
	APIToken string `yaml:"api_token" json:"api_token"`
}

type APIConfig struct {
	Listen string `yaml:"listen" json:"listen"`
}

func DefaultConfig() *Config {
	return &Config{
		Forward: ForwardConfig{
			Enabled: true,
			Listen:  ":10001",
		},
		Reverse: ReverseConfig{
			Enabled: true,
			Listen:  ":9999",
			TLS:     false,
			Cert:    ".cache/cert.pem",
			Key:     ".cache/key.pem",
			Routes: []RouteConfig{
				{Path: "/server/", Target: "http://127.0.0.1:8080"},
			},
		},
		DDNS: DDNSConfig{
			Enabled:  false,
			Interval: 600,
		},
		Cert: CertConfig{
			Enabled: false,
			Cert:    ".cache/cert.pem",
			Key:     ".cache/key.pem",
		},
		API: APIConfig{
			Listen: ":10000",
		},
	}
}

func (config *Config) Save(filename string) error {
	data, err := yaml.Marshal(config)
	if err != nil {
		return err
	}

	return os.WriteFile(filename, data, 0o644)
}

func LoadConfig(filename string) *Config {
	config := DefaultConfig()

	data, err := os.ReadFile(filename)
	if err != nil {
		if os.IsNotExist(err) {
			if err := config.Save(filename); err != nil {
				log.Fatalf("Config: Failed to save: %v", err)
			}
			return config
		}
		log.Fatalf("Config: Failed to read: %v", err)
	}

	if err := yaml.Unmarshal(data, config); err != nil {
		log.Fatalf("Config: Failed to parse: %v", err)
	}
	return config
}
