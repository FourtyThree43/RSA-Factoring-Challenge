package main

import (
	"bufio"
	"fmt"
	"math/big"
	"os"
)

func isPrime(n *big.Int) bool {
	// Check if n is divisible by 2
	if new(big.Int).Mod(n, big.NewInt(2)).Cmp(big.NewInt(0)) == 0 {
		return n.Cmp(big.NewInt(2)) == 0
	}

	// Check odd numbers starting from 3
	// up to the square root of n
	sqrt := new(big.Int).Sqrt(n)
	for i := big.NewInt(3); i.Cmp(sqrt) <= 0; i.Add(i, big.NewInt(2)) {
		if new(big.Int).Mod(n, i).Cmp(big.NewInt(0)) == 0 {
			return false
		}
	}

	return true
}

func factorize(n *big.Int) (*big.Int, *big.Int) {
	// Check if n is prime
	if isPrime(n) {
		return n, big.NewInt(1)
	}

	// Find the smallest prime factor of n
	one := big.NewInt(1)
	two := big.NewInt(2)
	for i := two; i.Cmp(n) < 0; i.Add(i, one) {
		if new(big.Int).Mod(n, i).Cmp(big.NewInt(0)) == 0 && isPrime(i) {
			return i, new(big.Int).Div(n, i)
		}
	}

	return n, one
}

func main() {
	args := os.Args[1:]
	if len(args) != 1 {
		fmt.Println("Usage: rsa <file>")
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
