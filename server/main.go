package main

import (
	"log"
)

func main() {
	dsn := "dbname=postgres"
	if err := InitDB(dsn); err != nil {
		log.Fatal(err)
	}

	r := SetupRouter()
	if err := r.Run(":8080"); err != nil {
		log.Fatal(err)
	}
}
