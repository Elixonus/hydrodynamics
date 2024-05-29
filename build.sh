mkdir -p bin
gcc -o bin/main src/main.c src/lib/sph.c src/lib/kernels.c src/lib/storage.c src/lib/memory.c src/lib/integrators.c -lm -std=c2x
# gcc src/test.c src/lib/sph.c src/lib/kernels.c -o bin/test -lm -std=c2x
