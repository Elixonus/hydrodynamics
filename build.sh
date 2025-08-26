#!/bin/bash
echo "creating executables"
shopt -s expand_aliases
alias gcc="gcc-14"
mkdir -p bin bin/lib
gcc -c src/lib/sph.c -o bin/lib/sph.o -DSPHAXES=2 -std=c23
echo "executables can now be found in bin/"
