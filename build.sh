mkdir -p bin
gcc src/test.c src/lib/sph.c src/lib/ker.h -o bin/test -std=c2x
