#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#define MAX_BUF_SIZE 256

__uint128_t gcd(__uint128_t a, __uint128_t b)
{
    if (a == 0)
    {
        return b;
    }
    return gcd(b % a, a);
}

/**
 * brent - Function that factors a number using Brent's modification
 *         to the Pollard's rho algorithm.
 * @n: Number to factorize.
 *
 * Return: A non-trivial factor of the number, or the number itself if it is prime.
 *
 * Description: Brent's algorithm is a modification of Pollard's rho algorithm
 *              that uses a cycle detection strategy to find a non-trivial factor of n.
 */
__uint128_t brent(__uint128_t n)
{
    if (n % 2 == 0)
    {
        return (2);
    }

    __uint128_t x = rand() % (n - 2) + 2;
    __uint128_t y = x;
    __uint128_t c = rand() % (n - 1) + 1;
    __uint128_t m = rand() % (n - 1) + 1;
    __uint128_t g = 1;
    __uint128_t r = 1;
    __uint128_t q = 1;

    while (g == 1)
    {
        x = y;
        for (__uint128_t i = 0; i < r; i++) {
            y = (y * y + c) % n;
        }
        __uint128_t k = 0;
        while (k < r && g == 1)
        {
            __uint128_t ys = y;
            for (__uint128_t i = 0; i < q && i < r - k; i++)
            {
                y = (y * y + c) % n;
                __uint128_t tmp = (x > y) ? x - y : y - x;
                g = gcd(tmp, n);
                if (g > 1) {
                    break;
                }
            }
            k += q;
        }
        r *= 2;
        q = q * (y > x ? y - x : x - y);
    }

    if (g == n)
    {
        while (true)
        {
            __uint128_t ys = (y * y + c) % n;
            __uint128_t tmp = (x > ys) ? x - ys : ys - x;
            g = gcd(tmp, n);
            if (g > 1) {
                break;
            }
            y = ys;
        }
    }

    return (g);
}
/**
 * factorize- Function that factors a number using Brent's modification
 *         to the Pollard's rho algorithm.
 * @n: Number to factorize.
 *
 * Return:  Void.
 */
void factorize(__uint128_t n, __uint128_t *p, __uint128_t *q)
{
    __uint128_t d = brent(n);

    *p = d;
    *q = n / d;
}

/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * Return: 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]) {
    char line[MAX_BUF_SIZE];
    FILE *input;
    __uint128_t n, p, q;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    while (fgets(line, sizeof(line), input) != NULL)
	{
        srand(time(NULL));
        n = strtoull(line, NULL, 10);
        factorize(n, &p, &q);
        printf("%llu=%llu*%llu\n", n, q, p);
    }
    fclose(input);
    exit(EXIT_SUCCESS);
}
