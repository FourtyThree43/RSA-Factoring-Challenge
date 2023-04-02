#!/usr/bin/python3
import random

nums = [4, 12, 34, 128, 1024, 4958, 1718944270642558716715,
        9, 99, 999, 9999, 9797973, 49, 239809320265259]

# Generate 100 more random numbers between 10^19 and 10^20
for i in range(1000):
    n = random.randint(2, 10**20)
    nums.append(n)

# Write the numbers to a file
with open('test00.txt', 'w') as f:
    f.write('\n'.join(str(n) for n in nums))
