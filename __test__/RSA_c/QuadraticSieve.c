#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define MAX_PRIME 1000000
#define MAX_FACTORS 10000
#define MAX_TERMS 10000

struct factor {
    uint64_t p;
    uint32_t e;
};

struct factorization {
    uint64_t n;
    uint32_t nfactors;
    struct factor factors[MAX_FACTORS];
};

struct factor_base {
    uint64_t prime[MAX_TERMS];
    uint32_t size;
};

struct sieve_data {
    uint64_t n;
    uint32_t m;
    uint32_t b[MAX_TERMS];
    uint32_t s[MAX_TERMS];
};

void init_factorization(struct factorization *f, uint64_t n) {
    f->n = n;
    f->nfactors = 0;
}

void add_factor(struct factorization *f, uint64_t p, uint32_t e) {
    if (f->nfactors < MAX_FACTORS) {
        f->factors[f->nfactors].p = p;
        f->factors[f->nfactors].e = e;
        f->nfactors++;
    }
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

void init_factor_base(struct factor_base *fb, uint32_t size) {
    fb->size = 0;
    for (uint32_t i = 2; i < MAX_PRIME && fb->size < size; i++) {
        if (is_prime(i)) {
            fb->prime[fb->size] = i;
            fb->size++;
        }
    }
}

void init_sieve_data(struct sieve_data *sd, uint64_t n, const struct factor_base *fb) {
    sd->n = n;
    sd->m = fb->size;
    for (uint32_t i = 0; i < sd->m; i++) {
        uint64_t p = fb->prime[i];
        uint64_t q = n / p;
        uint32_t j = 0;
        while ((q & 1) == 0) {
            j++;
            q >>= 1;
        }
        sd->b[i] = j;
        sd->s[i] = q % p;
    }
}

uint64_t pow_mod(uint64_t x, uint64_t y, uint64_t m) {
    uint64_t z = 1;
    while (y != 0) {
        if ((y & 1) != 0) {
            z = (z * x) % m;
        }
        x = (x * x) % m;
        y >>= 1;
    }
    return z;
}

uint64_t gcd(uint64_t a, uint64_t b) {
    uint64_t t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

uint64_t find_factor(uint64_t n) {
    uint64_t x = sqrt(n) + 1;
    uint64_t y = x * x - n;
    while (true) {
        uint64_t z = sqrt(y);
        if (z * z == y) {
            return x - z;
        }
        x++;
        y = x * x - n;
    }
}

void factor(uint64_t n, struct factorization *f, const struct factor_base *fb, struct sieve_data *sd)
{
    init_factorization(f, n);
    uint64_t x = sqrt(n) + 1;
    uint64_t y = x * x - n;

    for (uint32_t i = 0; i < sd->m && f->nfactors < MAX_FACTORS; i++) {
        uint64_t p = fb->prime[i];
        uint32_t e = 0;
        while (sd->s[i] == 0) {
            e++;
            sd->s[i] = pow_mod(x, sd->b[i], p);
        }
        uint64_t q = sd->s[i];
        for (uint32_t j = 1; j <= e && f->nfactors < MAX_FACTORS; j++) {
            uint64_t r = gcd(n, q - p);
            if (r > 1 && r < n) {
                add_factor(f, r, 1);
                n /= r;
                q /= r;
                y = x * x - n;
                x = sqrt(n) + 1;
            }
            q = (q * sd->s[i]) % p;
        }
    }

    if (n > 1) {
        uint64_t f1 = find_factor(n);
        uint64_t f2 = n / f1;
        add_factor(f, f1, 1);
        add_factor(f, f2, 1);
    }
}

int main(int argc, char *argv[])
{
    char line[1024];
    FILE *file;

    if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Cannot open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
    while (fgets(line, sizeof(line), file) != NULL) {
        struct factorization f;
        struct factor_base fb;
        struct sieve_data sd;
        uint64_t n = strtoull(line, NULL, 10);
        init_factor_base(&fb, MAX_TERMS);
        init_sieve_data(&sd, n, &fb);
        factor(n, &f, &fb, &sd);

        printf("%llu=", n);
        for (uint32_t i = 0; i < f.nfactors; i++) {
            printf("%llu", f.factors[i].p);
            if (f.factors[i].e > 1) {
                printf("^%u", f.factors[i].e);
            }
            if (i < f.nfactors - 1) {
                printf("*");
            }
        }
        printf("\n");
    }
    return 0;
}
