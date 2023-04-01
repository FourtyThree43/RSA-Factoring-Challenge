# RSA-Factoring-Challenge

RSA Factoring Challenge

## Tasks

### 0. Factorize all the things!

The factors program takes a file containing natural numbers to factor as input and factorizes as many numbers as possible into a product of two smaller numbers.

``Usage: factors <file>``

Where `<file>` is a file containing natural numbers to factor. One number per line. You can assume that all lines will be valid natural numbers greater than 1. You can assume that there will be no empty line, and no space before and after the valid number. The file will always end with a new line.

Output format: `n=p*q` one factorization per line. `p` and `q` don’t have to be prime numbers.

```gcc -Wall -Werror -Wextra -pedantic -lm factors.c -o factors```

Example:

        $ cat __test__/test00
        4
        12
        34
        128
        1024
        4958
        1718944270642558716715
        9
        99
        999
        9999
        9797973
        49
        239809320265259

        $ time ./factors __test__/test00
        4=2*2
        12=6*2
        34=17*2
        128=64*2
        1024=512*2
        4958=2479*2
        1718944270642558716715=343788854128511743343*5
        9=3*3
        99=33*3
        999=333*3
        9999=3333*3
        9797973=3265991*3
        49=7*7
        239809320265259=15485783*15485773

        real    0m0.009s
        user    0m0.008s
        sys 0m0.001s

### 1. RSA Factoring Challenge

The rsa program factorizes a single RSA number n into its prime factors p and q. The RSA number is provided in a file as input.

``Usage: rsa <file>``

Where `<file>` is a file containing a single RSA number. You can assume that the number will be a valid RSA number.

Output format: `n=p*q` where `p` and `q` are prime numbers.

```gcc -Wall -Werror -Wextra -pedantic -lm rsa.c -o rsa```

Example:

        $ cat __test__/rsa-1
        6
        $ ./rsa __test__/rsa-1
        6=3*2
        $ cat __test__/rsa-2
        77
        $ ./rsa __test__/rsa-2
        77=11*7
        $ [...]
        $ cat __test__/rsa-15
        239821585064027
        $ ./rsa __test__/rsa-15
        239821585064027=15486481*15485867
