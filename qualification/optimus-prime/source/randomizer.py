

import sympy
import random


def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)


print 'Getting p and q...'
while True:
    p = sympy.randprime(2**120, 2**150)
    q = sympy.randprime(2**120, 2**150)
    if gcd((p - 1) * (q - 1), 65537) == 1:
        break

print 'Got p and q!'
print
print 'Getting random numbers...'

random_numbers = [(random.randrange(2**50, 2**100) * random.randrange(2**50, 2**100)) for _ in range(10**7)]

print 'Got random numbers!'
print
print 'Getting random primes...'

for i in range(1268):
    random_numbers[random.randint(0, 10**7)] = sympy.randprime(2**120, 2**150)
random_numbers[random.randint(0, 10**7)] = p
random_numbers[random.randint(0, 10**7)] = q

print 'Got random primes!'

print 'Writing to nums.txt...'

with open('nums.txt', 'w') as f:
    for i in random_numbers:
        f.write(str(i) + '\n')

print "Written to nums.txt!"

flag = ''

with open('flag.txt', 'r') as f:
    flag = f.readline()

n = p * q
e = 65537
c = pow(int(flag.encode('hex'), 16), e, n)

print '=' * 20
print 'e:', e
print 'c:', c
print '=' * 20

with open('rsa.txt', 'w') as f:
    f.write('e: ' + str(e) + '\n')
    f.write('c: ' + str(c) + '\n')

print "Written e and c to rsa.txt!"
print
