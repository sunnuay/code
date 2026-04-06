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

func (s *grpcServer) Handle(ctx context.Context, req *api.Request) (*api.Response, error) {
	return &api.Response{ResponseText: "Hello " + req.RequestText + " from gRPC!"}, nil
}

func startGRPCServer() {
	lis, err := net.Listen("tcp", ":50051")
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	s := grpc.NewServer()
	api.RegisterCoreServer(s, &grpcServer{})

	log.Println("gRPC Server running on :50051")
	if err := s.Serve(lis); err != nil {
		log.Fatalf("Failed to serve gRPC: %v", err)
	}
}

func startGinServer() {
	conn, err := grpc.NewClient(
		"localhost:50051",
		grpc.WithTransportCredentials(insecure.NewCredentials()),
	)
	if err != nil {
		log.Fatalf("Failed to connect to gRPC server: %v", err)
	}
	defer func() {
		if err := conn.Close(); err != nil {
			log.Printf("Failed to close gRPC connection: %v", err)
		}
	}()

	grpcClient := api.NewCoreClient(conn)

	gin.SetMode(gin.ReleaseMode)
	r := gin.Default()

	if err := r.SetTrustedProxies(nil); err != nil {
		log.Fatalf("Failed to set trusted proxies: %v", err)
	}

	r.GET("/hello/:name", func(c *gin.Context) {
		name := c.Param("name")

		req := &api.Request{RequestText: name}

		resp, err := grpcClient.Handle(context.Background(), req)
		if err != nil {
			c.JSON(500, gin.H{"error": err.Error()})
			return
		}

		c.JSON(200, gin.H{
			"code": 200,
			"data": resp.ResponseText,
		})
	})

	log.Println("Gin HTTP Server running on :8080")
	if err := r.Run(":8080"); err != nil {
		log.Fatalf("Failed to run Gin server: %v", err)
	}
}

func main() {
	go startGRPCServer()
	go startGinServer()
	select {}
}
