package main

import (
	"log"
)

func main() {
	dsn := "dbname=postgres"

	if err := InitDB(dsn); err != nil {
		log.Fatalf("Failed to connect to database: %v", err)
	}

	r := SetupRouter()

	if err := r.Run(":8080"); err != nil {
		log.Fatalf("Failed to start server: %v", err)
	}
}
