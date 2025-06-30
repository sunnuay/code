//go:build ignore

package main

import (
	"code/sort"
	"fmt"
)

func main() {
	arr := []int{5, 12, 15, 11, 3, 8, 13, 9, 4, 7, 10, 2, 14, 1, 6}
	sort.Ints(arr)
	fmt.Println(arr)
}
