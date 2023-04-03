package main

import (
	"bufio"
	"fmt"
	"math/big"
	"os"
)

// trial division algorithm
func factorize(n *big.Int) (*big.Int, *big.Int) {
	one := big.NewInt(1)
	two := big.NewInt(2)
	zero := big.NewInt(0)

	// Check if n is even
	if new(big.Int).Mod(n, two).Cmp(zero) == 0 {
		return two, new(big.Int).Div(n, two)
	}

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
		p, q := factorize_3(n)
		fmt.Printf("%v=%v*%v\n", n, q, p)
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error reading file:", err)
		return
	}
}

func factorize_2(n *big.Int) (*big.Int, *big.Int) {
	one := big.NewInt(1)
	two := big.NewInt(2)
	zero := big.NewInt(0)
	sqrtN := new(big.Int).Sqrt(n)

	// Check if n is a prime using Miller-Rabin primality test
	if n.ProbablyPrime(10) {
		return n, one
	}

	for i := two; i.Cmp(sqrtN) <= 0; i.Add(i, one) {
		if new(big.Int).Mod(n, i).Cmp(zero) == 0 {
			return i, new(big.Int).Div(n, i)
		}
	}
	return n, one
}

// factorize that uses precomplied primes to speed up the factorization process:
func factorize_3(n *big.Int) (*big.Int, *big.Int) {
	one := big.NewInt(1)
	two := big.NewInt(2)
	zero := big.NewInt(0)
	primes := []int64{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
		71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
		163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
		257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353,
		359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457,
		461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571,
		577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673,
		677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
		809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
		919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997}
	// Check if n is even
	if new(big.Int).Mod(n, two).Cmp(zero) == 0 {
		return two, new(big.Int).Div(n, two)
	}
	// Check if n is a prime using Miller-Rabin primality test
	if n.ProbablyPrime(10) {
		return n, one
	}
	for _, p := range primes {
		pBigInt := big.NewInt(p)
		if new(big.Int).Mod(n, pBigInt).Cmp(zero) == 0 {
			return pBigInt, new(big.Int).Div(n, pBigInt)
		}
	}
	for i := new(big.Int).SetInt64(primes[len(primes)-1]); i.Cmp(n) < 0; i.Add(i, two) {
		if new(big.Int).Mod(n, i).Cmp(zero) == 0 {
			return i, new(big.Int).Div(n, i)
		}
	}
	return n, one
}
