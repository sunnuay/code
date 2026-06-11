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
	Email    string `yaml:"email" json:"email"`
	CacheDir string `yaml:"cache_dir" json:"cache_dir"`
	Domain   string `yaml:"domain" json:"domain"`
	APIToken string `yaml:"api_token" json:"api_token"`
}

type APIConfig struct {
	Listen string `yaml:"listen" json:"listen"`
}

func DefaultConfig() *Config {
	return &Config{
		API: APIConfig{
			Listen: ":9999",
		},
		Forward: ForwardConfig{
			Enabled: false,
			Listen:  ":10000",
		},
		Reverse: ReverseConfig{
			Enabled: false,
			Listen:  ":10001",
			Routes: []RouteConfig{
				{Path: "/api/", Target: "http://127.0.0.1:8080"},
			},
		},
		DDNS: DDNSConfig{
			Enabled:  false,
			Interval: 600,
		},
		Cert: CertConfig{
			Enabled:  false,
			CacheDir: "./cert",
		},
	}
}

func LoadConfig(filename string) *Config {
	data, err := os.ReadFile(filename)
	if err != nil {
		if os.IsNotExist(err) {
			cfg := DefaultConfig()
			if err := cfg.Save(filename); err != nil {
				log.Fatalf("Failed to save default config: %v", err)
			}
			return cfg
		}
		log.Fatalf("Failed to read config: %v", err)
	}

	cfg := DefaultConfig()
	if err := yaml.Unmarshal(data, cfg); err != nil {
		log.Fatalf("Failed to parse config: %v", err)
	}
	return cfg
}

func (c *Config) Save(filename string) error {
	data, err := yaml.Marshal(c)
	if err != nil {
		return err
	}
	return os.WriteFile(filename, data, 0o644)
}
