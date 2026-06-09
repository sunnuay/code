package main

import (
	"encoding/json"
	"log"
	"net/http"
	"sync"
)

type APIHandler struct {
	mu         sync.RWMutex
	config     *Config
	configPath string
}

func NewAPIHandler(cfg *Config, configPath string) *APIHandler {
	return &APIHandler{config: cfg, configPath: configPath}
}

func (h *APIHandler) GetConfig() *Config {
	h.mu.RLock()
	defer h.mu.RUnlock()
	return h.config
}

func writeJSONError(w http.ResponseWriter, code int, msg string) {
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(code)
	json.NewEncoder(w).Encode(map[string]string{"error": msg})
}

func corsMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Access-Control-Allow-Methods", "GET, PUT, PATCH, OPTIONS")
		w.Header().Set("Access-Control-Allow-Headers", "Content-Type")
		if r.Method == http.MethodOptions {
			w.WriteHeader(http.StatusOK)
			return
		}
		next.ServeHTTP(w, r)
	})
}

func (h *APIHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	switch {
	case r.URL.Path == "/api/config" && r.Method == http.MethodGet:
		h.handleGetConfig(w, r)
	case r.URL.Path == "/api/config" && r.Method == http.MethodPut:
		h.handlePutConfig(w, r)
	case r.URL.Path == "/api/status" && r.Method == http.MethodGet:
		h.handleGetStatus(w, r)
	default:
		writeJSONError(w, http.StatusNotFound, "not found")
	}
}

func (h *APIHandler) handleGetConfig(w http.ResponseWriter, r *http.Request) {
	h.mu.RLock()
	defer h.mu.RUnlock()

	w.Header().Set("Content-Type", "application/json")
	if err := json.NewEncoder(w).Encode(h.config); err != nil {
		log.Printf("API: Failed to encode config: %v", err)
	}
}

func (h *APIHandler) handlePutConfig(w http.ResponseWriter, r *http.Request) {
	var newCfg Config
	if err := json.NewDecoder(r.Body).Decode(&newCfg); err != nil {
		writeJSONError(w, http.StatusBadRequest, "invalid JSON: "+err.Error())
		return
	}

	h.mu.Lock()
	h.config = &newCfg
	h.mu.Unlock()

	if err := h.config.Save(h.configPath); err != nil {
		writeJSONError(w, http.StatusInternalServerError, "failed to save config: "+err.Error())
		return
	}

	log.Printf("API: Config updated and saved")
	h.handleGetConfig(w, r)
}

func (h *APIHandler) handleGetStatus(w http.ResponseWriter, r *http.Request) {
	h.mu.RLock()
	defer h.mu.RUnlock()

	status := map[string]map[string]bool{
		"forward": {
			"enabled": h.config.Forward.Enabled,
			"running": h.config.Forward.Enabled,
		},
		"reverse": {
			"enabled": h.config.Reverse.Enabled,
			"running": h.config.Reverse.Enabled,
		},
		"ddns": {
			"enabled": h.config.DDNS.Enabled,
			"running": h.config.DDNS.Enabled,
		},
		"cert": {
			"enabled": h.config.Cert.Enabled,
			"running": h.config.Cert.Enabled,
		},
	}

	w.Header().Set("Content-Type", "application/json")
	if err := json.NewEncoder(w).Encode(status); err != nil {
		log.Printf("API: Failed to encode status: %v", err)
	}
}

func StartWebAPI(cfg *WebAPIConfig, handler *APIHandler) {
	mux := http.NewServeMux()
	mux.Handle("/api/", handler)

	server := &http.Server{
		Addr:    cfg.Listen,
		Handler: corsMiddleware(mux),
	}

	log.Printf("API: Listening on %s", cfg.Listen)
	if err := server.ListenAndServe(); err != nil {
		log.Fatalf("API: Listen error: %v", err)
	}
}
