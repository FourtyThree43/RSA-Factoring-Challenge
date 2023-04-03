package main

import (
	"bufio"
	"fmt"
	"math/big"
	"os"
)

func factorize(n *big.Int) (*big.Int, *big.Int) {
	one := big.NewInt(1)
	two := big.NewInt(2)
	zero := big.NewInt(0)

	for i := two; i.Cmp(n) < 0; i.Add(i, one) {
		if new(big.Int).Mod(n, i).Cmp(zero) == 0 {
			return i, new(big.Int).Div(n, i)
		}
	}
	return n, one
}

func main() {
	args := os.Args[1:]
	if len(args) != 1 {
		fmt.Println("Usage: factors <file>")
		return
	}

	filename := args[0]
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		n := new(big.Int)
		_, ok := n.SetString(scanner.Text(), 10)
		if !ok {
			fmt.Println("Error parsing number:", scanner.Text())
			continue
		}
		p, q := factorize(n)
		fmt.Printf("%v=%v*%v\n", n, q, p)
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error reading file:", err)
		return
	}
}
