#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define BUFSIZE 2048

uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

uint64_t pollard_rho(uint64_t n) {
    uint64_t x = rand() % (n - 2) + 2;
    uint64_t y = x;
    uint64_t c = rand() % (n - 1) + 1;
    uint64_t d = 1;
    while (d == 1) {
        x = (x * x + c) % n;
        y = (y * y + c) % n;
        y = (y * y + c) % n;
        d = gcd(abs(x - y), n);
    }
    if (d == n) {
        return pollard_rho(n);
    }
    return d;
}

bool is_prime(uint64_t n) {
    if (n < 2) {
        return false;
    }
    for (uint64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    char buf[BUFSIZE];

    if (argc != 2) {
        printf("Usage: rsa_factoring_challenge <file>\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }
    while (fgets(buf, BUFSIZE, input) != NULL)
	{
        uint64_t n, p, q;

        n = strtoull(buf, NULL, 10);
        p = pollard_rho(n);
        q = n / p;
        printf("%llu=%llu*%llu\n", n, p, q);
    }

    fclose(input);
    return 0;
}
