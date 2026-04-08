package main

import (
	"context"
	"encoding/base64"
	"log"
	"net"

	"code/server/api"

	"google.golang.org/grpc"
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

func grpcServer() {
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
