package main

import (
	"context"
	"log"
	"net"

	"code/server/api"

	"github.com/gin-gonic/gin"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

type grpcServer struct {
	api.UnimplementedCoreServer
}

func (s *grpcServer) Handle(_ context.Context, req *api.Request) (*api.Response, error) {
	return &api.Response{ResponseText: req.RequestText + "..."}, nil
}

func startGRPCServer() {
	lis, err := net.Listen("tcp", ":9998")
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	s := grpc.NewServer()
	api.RegisterCoreServer(s, &grpcServer{})
	if err := s.Serve(lis); err != nil {
		log.Fatalf("Failed to run gRPC: %v", err)
	}
}

func startGinServer() {
	conn, err := grpc.NewClient(":9998", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatalf("Failed to connect to gRPC: %v", err)
	}

	grpcClient := api.NewCoreClient(conn)
	gin.SetMode(gin.ReleaseMode)
	r := gin.Default()

	r.GET("/:name", func(c *gin.Context) {
		resp, err := grpcClient.Handle(c.Request.Context(), &api.Request{RequestText: c.Param("name")})
		if err != nil {
			c.JSON(500, gin.H{"error": err.Error()})
			return
		}
		c.JSON(200, gin.H{"code": 200, "data": resp.ResponseText})
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
