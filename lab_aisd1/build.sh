#!/bin/bash
gcc -c -g 1.c
gcc -c -g indiv.c
gcc indiv.o 1.o -o a.out
valgrind ./a.out
