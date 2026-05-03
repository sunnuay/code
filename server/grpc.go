package main

import (
	"context"
	"server/api"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

func client(text string) (string, error) {
	opts := grpc.WithTransportCredentials(insecure.NewCredentials())
	conn, err := grpc.NewClient("127.0.0.1:50051", opts)
	if err != nil {
		return "", err
	}

	defer func() { _ = conn.Close() }()

	resp, err := api.NewCoreClient(conn).Handle(context.Background(), &api.Request{Text: text})
	if err != nil {
		return "", err
	}

	return resp.Text, nil
}
