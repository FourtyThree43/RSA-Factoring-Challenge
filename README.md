# RSA-Factoring-Challenge

RSA Factoring Challenge

## Tasks

### 0. Factorize all the things!

The factors program takes a file containing natural numbers to factor as input and factorizes as many numbers as possible into a product of two smaller numbers.

``Usage: factors <file>``

Where `<file>` is a file containing natural numbers to factor. One number per line. You can assume that all lines will be valid natural numbers greater than 1. You can assume that there will be no empty line, and no space before and after the valid number. The file will always end with a new line.

Output format: `n=p*q` one factorization per line. `p` and `q` don’t have to be prime numbers.

```gcc -Wall -Werror -Wextra -pedantic -lm factors.c -o factors```


### 1. RSA Factoring Challenge

The rsa program factorizes a single RSA number n into its prime factors p and q. The RSA number is provided in a file as input.

``Usage: rsa <file>``

Where `<file>` is a file containing a single RSA number. You can assume that the number will be a valid RSA number.

Output format: `n=p*q` where `p` and `q` are prime numbers.

```gcc -Wall -Werror -Wextra -pedantic -lm rsa.c -o rsa```

