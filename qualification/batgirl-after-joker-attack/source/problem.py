#!/usr/bin/env python2.7

from Crypto.Cipher import AES

import hashlib, random, sys

class Unbuffered(object):
   def __init__(self, stream):
       self.stream = stream
   def write(self, data):
       self.stream.write(data)
       self.stream.flush()
   def writelines(self, datas):
       self.stream.writelines(datas)
       self.stream.flush()
   def __getattr__(self, attr):
       return getattr(self.stream, attr)

sys.stdout = Unbuffered(sys.stdout)


header = 'ALPHA-OMEGA-BEAM-221'
footer = 'DETECTIVE-2341'

keyfile = open('key.txt')
key = keyfile.read().decode('hex')
keyfile.close()
flagfile = open('flag.txt')
flag = flagfile.read()
flagfile.close()
name = raw_input('This is b*tcave with advance security. Tell me your name: ')

def enc(msg):
    msg += hashlib.sha256(msg).digest()
    iv = ''
    for i in range(16):
        iv += chr(random.randint(0, 255))
    cipher = AES.new(key, AES.MODE_CBC, iv)
    msg += chr(16 - len(msg)%16) * (16 - len(msg)%16)
    return iv.encode('hex') + cipher.encrypt(msg).encode('hex')

def dec(enc):
    enc = enc.decode('hex')
    iv = enc[:16]
    enc = enc[16:]
    cipher = AES.new(key, AES.MODE_CBC, iv)
    raw_text = cipher.decrypt(enc)
    if ord(raw_text[-1]) <= 0 or ord(raw_text[-1]) > 16:
        return 'FAIL'
    unppaded_text = raw_text[:-ord(raw_text[-1])]
    hashed = unppaded_text[-32:]
    msg = unppaded_text[:-32]
    if hashlib.sha256(msg).digest() != hashed:
        return 'FAIL'
    return 'SUCCESS, B*tman understand what you mean'

if __name__ == '__main__':
    while True:
        opt = raw_input('''
    Menu:
    S - Send message to B*tman
    D - Decrypt leaked info
''')
        if 'S' in opt:
            message = raw_input('What message you wanna tell to Mr. Br*ce W*yne?\n')
            chunks = '''
===={}====
{}
===={}====
{}
===={}====
'''.format(header, message, flag, message.encode('base64'), footer)
            print enc(chunks), 'send to Mr. Br*ce'
        else:
            info = raw_input('What info you get?\n')
            print dec(info)
