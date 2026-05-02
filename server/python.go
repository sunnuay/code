package main

import (
	"context"
	"server/api"
	"time"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

func python(input string) (string, error) {
	conn, err := grpc.NewClient(
		"127.0.0.1:50051",
		grpc.WithTransportCredentials(insecure.NewCredentials()),
	)
	if err != nil {
		return "", err
	}
	defer func() { _ = conn.Close() }()

	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	resp, err := api.NewCoreClient(conn).
		Handle(ctx, &api.Request{Text: input})
	if err != nil {
		return "", err
	}

	return resp.Text, nil
}
