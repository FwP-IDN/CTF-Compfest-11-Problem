#! /bin/sh
gcc -no-pie -fno-stack-protector source.c -o problem
strip problem
