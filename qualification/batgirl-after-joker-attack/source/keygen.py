#!/usr/bin/env python2.7

import random
key = ''
for i in range(16):
    key += chr(random.randint(0, 255))

print key.encode('hex')
