package main

import (
	"fmt"
	"os"

	"gopkg.in/yaml.v3"
)

type WebAPIConfig struct {
	Listen string `yaml:"listen" json:"listen"`
}

type Config struct {
	WebAPI  WebAPIConfig  `yaml:"webapi" json:"webapi"`
	Forward ForwardConfig `yaml:"forward" json:"forward"`
	Reverse ReverseConfig `yaml:"reverse" json:"reverse"`
	DDNS    DDNSConfig    `yaml:"ddns" json:"ddns"`
	Cert    CertConfig    `yaml:"cert" json:"cert"`
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
	APIToken string `yaml:"api_token" json:"api_token"`
	ZoneID   string `yaml:"zone_id" json:"zone_id"`
	Domain   string `yaml:"domain" json:"domain"`
}

type CertConfig struct {
	Enabled  bool   `yaml:"enabled" json:"enabled"`
	Email    string `yaml:"email" json:"email"`
	CacheDir string `yaml:"cache_dir" json:"cache_dir"`
	APIToken string `yaml:"api_token" json:"api_token"`
	ZoneID   string `yaml:"zone_id" json:"zone_id"`
	Domain   string `yaml:"domain" json:"domain"`
}

func DefaultConfig() *Config {
	return &Config{
		WebAPI: WebAPIConfig{
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

func LoadConfig(filename string) (*Config, error) {
	data, err := os.ReadFile(filename)
	if err != nil {
		if os.IsNotExist(err) {
			cfg := DefaultConfig()
			if err := cfg.Save(filename); err != nil {
				return nil, fmt.Errorf("failed to save default config: %w", err)
			}
			return cfg, nil
		}
		return nil, err
	}

	cfg := DefaultConfig()
	if err := yaml.Unmarshal(data, cfg); err != nil {
		return nil, err
	}
	return cfg, nil
}

func (c *Config) Save(filename string) error {
	data, err := yaml.Marshal(c)
	if err != nil {
		return err
	}
	return os.WriteFile(filename, data, 0o644)
}
