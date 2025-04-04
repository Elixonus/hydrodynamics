#!/bin/bash
echo "creating executables"
shopt -s expand_aliases
alias gcc="gcc-14"
mkdir bin
gcc -c src/sph.c -o bin/sph.o -std=c23
gcc src/solvetruss.c -o bin/solvetruss bin/dampspring.o -lm -std=c23
gcc src/rendertruss.c -o bin/rendertruss bin/dampspring.o -lm $(pkg-config --cflags --libs cairo) -std=c23
echo "executables can now be found in bin/"
