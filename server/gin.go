package main

import (
	"log"

	"code/server/api"

	"github.com/gin-gonic/gin"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

func ginServer() {
	conn, err := grpc.NewClient(":9998", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatalf("Failed to connect to gRPC: %v", err)
	}

	coreClient := api.NewCoreClient(conn)
	gin.SetMode(gin.ReleaseMode)
	r := gin.Default()

	r.GET("/api", func(c *gin.Context) {
		resp, err := coreClient.Handle(c.Request.Context(), &api.Request{Text: c.Query("base64")})
		if err != nil {
			c.JSON(500, gin.H{"error": "invalid base64"})
			return
		}
		c.JSON(200, gin.H{"data": resp.Text})
	})

	if err := r.Run(":10002"); err != nil {
		log.Fatalf("Failed to run Gin: %v", err)
	}
}
