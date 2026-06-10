package main

import (
	"encoding/json"
	"log"
	"net/http"
	"os"
	"syscall"
	"time"
)

func writeJSON(w http.ResponseWriter, code int, data any) {
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(code)
	json.NewEncoder(w).Encode(data)
}

func corsMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Access-Control-Allow-Methods", "GET, PUT, PATCH, POST, OPTIONS")
		w.Header().Set("Access-Control-Allow-Headers", "Content-Type")
		if r.Method == http.MethodOptions {
			w.WriteHeader(http.StatusOK)
			return
		}
		next.ServeHTTP(w, r)
	})
}

func StartAPI(cfg *Config, configPath string) {
	mux := http.NewServeMux()

	mux.HandleFunc("/api/config", func(w http.ResponseWriter, r *http.Request) {
		switch r.Method {
		case http.MethodGet:
			writeJSON(w, http.StatusOK, cfg)

		case http.MethodPut:
			var newCfg Config
			if err := json.NewDecoder(r.Body).Decode(&newCfg); err != nil {
				writeJSON(w, http.StatusBadRequest, map[string]string{"error": "invalid JSON: " + err.Error()})
				return
			}
			*cfg = newCfg
			if err := cfg.Save(configPath); err != nil {
				writeJSON(w, http.StatusInternalServerError, map[string]string{"error": "failed to save: " + err.Error()})
				return
			}
			log.Print("API: Config updated and saved")
			writeJSON(w, http.StatusOK, cfg)

		default:
			writeJSON(w, http.StatusMethodNotAllowed, map[string]string{"error": "method not allowed"})
		}
	})

	mux.HandleFunc("/api/status", func(w http.ResponseWriter, _ *http.Request) {
		writeJSON(w, http.StatusOK, map[string]map[string]bool{
			"forward": {"enabled": cfg.Forward.Enabled, "running": cfg.Forward.Enabled},
			"reverse": {"enabled": cfg.Reverse.Enabled, "running": cfg.Reverse.Enabled},
			"ddns":    {"enabled": cfg.DDNS.Enabled, "running": cfg.DDNS.Enabled},
			"cert":    {"enabled": cfg.Cert.Enabled, "running": cfg.Cert.Enabled},
		})
	})

	mux.HandleFunc("/api/restart", func(w http.ResponseWriter, _ *http.Request) {
		writeJSON(w, http.StatusOK, map[string]string{"status": "restarting"})

		go func() {
			time.Sleep(200 * time.Millisecond)
			log.Print("API: Restarting process...")
			execPath, err := os.Executable()
			if err != nil {
				log.Fatalf("API: Restart failed: %v", err)
			}
			if err := syscall.Exec(execPath, os.Args, os.Environ()); err != nil {
				log.Fatalf("API: Restart failed: %v", err)
			}
		}()
	})

	server := &http.Server{
		Addr:    cfg.API.Listen,
		Handler: corsMiddleware(mux),
	}

	log.Printf("API: Listening on %s", cfg.API.Listen)
	log.Fatal(server.ListenAndServe())
}
