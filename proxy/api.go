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

func StartAPI(config *Config, configPath string) {
	mux := http.NewServeMux()

	mux.HandleFunc("GET /api/config", func(w http.ResponseWriter, r *http.Request) {
		writeJSON(w, http.StatusOK, config)
	})

	mux.HandleFunc("POST /api/config", func(w http.ResponseWriter, r *http.Request) {
		var newConfig Config
		if err := json.NewDecoder(r.Body).Decode(&newConfig); err != nil {
			writeJSON(w, http.StatusBadRequest, map[string]string{
				"error": "invalid JSON: " + err.Error(),
			})
			return
		}
		if err := newConfig.Save(configPath); err != nil {
			writeJSON(w, http.StatusInternalServerError, map[string]string{
				"error": "failed to save: " + err.Error(),
			})
			return
		}
		*config = newConfig
		log.Print("API: Config updated and saved")
		writeJSON(w, http.StatusOK, config)
	})

	mux.HandleFunc("POST /api/restart", func(w http.ResponseWriter, r *http.Request) {
		writeJSON(w, http.StatusOK, map[string]string{
			"status": "restarting",
		})
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

	server := &http.Server{Addr: config.API.Listen, Handler: corsMiddleware(mux)}
	log.Printf("API: Listening on %s", config.API.Listen)
	log.Fatal(server.ListenAndServe())
}

func corsMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Access-Control-Allow-Methods", "GET, POST")
		w.Header().Set("Access-Control-Allow-Headers", "Content-Type")
		if r.Method == http.MethodOptions {
			w.WriteHeader(http.StatusOK)
			return
		}
		next.ServeHTTP(w, r)
	})
}
