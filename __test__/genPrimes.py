#!/usr/bin/python3
import random

def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

def generate_composite_numbers():
    n = 10000
    composite_numbers = []
    while len(composite_numbers) < n:
        x = random.randint(2, 10**12)
        if not is_prime(x):
            composite_numbers.append(x)
    return composite_numbers

with open('test.txt', 'w') as f:
    for num in generate_composite_numbers():
        f.write(str(num) + '\n')
