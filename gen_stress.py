from random import randint
n = randint(1_000_000, 1_000_000_0)
print(n)
print(' '.join(map(str, range(1, n+1))))
