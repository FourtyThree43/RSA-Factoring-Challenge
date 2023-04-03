#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define MAX_BUF_SIZE 256

static uint64_t gcd(uint64_t a, uint64_t b)
{
    while (b)
    {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
return a;
}

static uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = 1;
    while (exponent > 0)
    {
        if (exponent & 1)
        {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}

static int is_prime(uint64_t n)
{
    uint64_t i;

    if (n == 2 || n == 3)
        return 1;
    else if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return 0;
    for (i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

static int rsa(char *filename)
{
    uint64_t n, p = 0, q = 0, phi, e, d = 0;
    FILE *fp;
    char buf[MAX_BUF_SIZE];

    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: could not open file %s\n", filename);
        return 1;
    }

    while (fgets(buf, MAX_BUF_SIZE, fp) != NULL)
    {
        n = strtoul(buf, NULL, 10);
        while (1)
        {
            p = rand() % (n - 1) + 1;
            if (is_prime(p))
                break;
        }
        while (1)
        {
            q = rand() % (n - 1) + 1;
            if (is_prime(q) && q != p)
                break;
        }
        phi = (p - 1) * (q - 1);
        e = 65537;

        while (1)
        {
            if (gcd(e, phi) == 1)
            {
                d = mod_pow(e, phi - 1, phi);
                break;
            }
            e++;
        }
        printf("%lu=%lu*%lu\n", n, p, q);
    }
    fclose(fp);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    if (rsa(filename) != 0)
    {
        printf("Error: failed to generate RSA keys\n");
        return 1;
    }
    return (EXIT_SUCCESS);
}
