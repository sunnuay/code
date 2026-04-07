package main

import (
	"context"
	"encoding/base64"
	"log"
	"net"

	"code/server/api"

	"github.com/gin-gonic/gin"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

type coreServer struct {
	api.UnimplementedCoreServer
}

func (s *coreServer) Handle(_ context.Context, req *api.Request) (*api.Response, error) {
	data, err := base64.StdEncoding.DecodeString(req.Text)
	if err != nil {
		return nil, err
	}
	return &api.Response{Text: string(data)}, nil
}

func startGRPCServer() {
	lis, err := net.Listen("tcp", ":9998")
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	s := grpc.NewServer()
	api.RegisterCoreServer(s, &coreServer{})
	if err := s.Serve(lis); err != nil {
		log.Fatalf("Failed to run gRPC: %v", err)
	}
}

func startGinServer() {
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

func main() {
	go startGRPCServer()
	go startGinServer()
	select {}
}
