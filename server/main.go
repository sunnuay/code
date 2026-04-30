package main

import (
	"context"
	"fmt"
	"server/api"
	"time"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

func main() {
	conn, err := grpc.NewClient("localhost:50051", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		panic(err)
	}
	defer func() { _ = conn.Close() }()

	client := api.NewCoreClient(conn)
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	resp, err := client.Handle(ctx, &api.Request{Text: "hello from go"})
	if err != nil {
		panic(err)
	}
	fmt.Println(resp.Text)
}
