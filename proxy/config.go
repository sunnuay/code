package main

import (
	"os"

	"gopkg.in/yaml.v3"
)

type Config struct {
	Forward ForwardConfig `yaml:"forward"`
	Reverse ReverseConfig `yaml:"reverse"`
	DDNS    DDNSConfig    `yaml:"ddns"`
}

type ForwardConfig struct {
	Enabled bool   `yaml:"enabled"`
	Listen  string `yaml:"listen"`
}

type ReverseConfig struct {
	Enabled bool          `yaml:"enabled"`
	Listen  string        `yaml:"listen"`
	Routes  []RouteConfig `yaml:"routes"`
}

type RouteConfig struct {
	Path   string `yaml:"path"`
	Target string `yaml:"target"`
}

type DDNSConfig struct {
	Enabled  bool   `yaml:"enabled"`
	Interval int    `yaml:"interval"`
	APIToken string `yaml:"api_token"`
	ZoneID   string `yaml:"zone_id"`
	Domain   string `yaml:"domain"`
}

func LoadConfig(filename string) (*Config, error) {
	data, err := os.ReadFile(filename)
	if err != nil {
		return nil, err
	}
	var cfg Config
	if err := yaml.Unmarshal(data, &cfg); err != nil {
		return nil, err
	}
	return &cfg, nil
}
