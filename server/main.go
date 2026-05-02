package main

import "fmt"

func main() {
	var word string
	for {
		_, _ = fmt.Scan(&word)
		fmt.Println(client(word))
	}
}
