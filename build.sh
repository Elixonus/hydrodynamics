#!/bin/bash
echo "creating executables"
shopt -s expand_aliases
alias gcc="gcc-14"
mkdir -p bin
gcc -c src/sph.c -o bin/sph.o -std=c23
echo "executables can now be found in bin/"
