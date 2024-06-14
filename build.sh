#!/bin/bash
mkdir -p bin
mkdir -p bin/obj
gcc -c src/lib/sph.c -o bin/obj/sph.o -std=c2x
gcc -c src/lib/kernels.c -o bin/obj/kernels.o -std=c2x
gcc -c src/lib/integrators.c -o bin/obj/integrators.o -std=c2x
gcc -c src/lib/simulation.c -o bin/obj/simulation.o -std=c2x
gcc -c src/lib/storage.c -o bin/obj/storage.o -std=c2x
gcc -c src/lib/memory.c -o bin/obj/memory.o -std=c2x
gcc src/main.c -o bin/fluid bin/obj/sph.o bin/obj/kernels.o bin/obj/integrators.o bin/obj/simulation.o bin/obj/storage.o bin/obj/memory.o -lm $(pkg-config --cflags --libs cairo) -std=c2x
