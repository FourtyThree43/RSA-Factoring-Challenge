#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/**
 * find_factor - Function that finds the smallest prime factor of a number.
 * @n: Number for which the smallest prime factor is to be found.
 *
 * Return: The smallest prime factor of the number,
 *          or the number itself if it is prime.
 */
unsigned long long find_factor(unsigned long long n)
{
	unsigned long long sqrt_n = sqrt(n);
	unsigned long long factor = 2;

	while (factor <= sqrt_n)
	{
		if (n % factor)
		{
			return (factor);
		}
		factor++;
	}
	return (n);
}

/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[])
{
	unsigned long long n, p, q;
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: factors <file>\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		/* Parse input number*/
		n = strtoull(line, NULL, 10);
		p = find_factor(n);
		q = n / p;
		printf("%llu=%llu*%llu\n", n, p, q);
	}
	free(line);
	fclose(file);
	return (0);
}
