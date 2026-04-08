package main

func main() {
	go grpcServer()
	go ginServer()
	select {}
}
