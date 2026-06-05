package main

func main() {
	InitDB("dbname=postgres")
	SetupRouter().Run("127.0.0.1:8080")
}
