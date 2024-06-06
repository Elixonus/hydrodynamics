#include <stdlib.h>
#include "sph.h"

struct particle {
	int id;
	double radius;
	double volume;
	struct s basic;
	double a[3];
};

struct cell {
	int id;
	double length;
	double center[3];
	int pcount;
	size_t pmemory;
	struct particle **particles;
};

int pid;
int pcount;
size_t pmemory;
struct particle *particles;

int cid;
double clength;
int ccount[3];
size_t cmemory[3];
struct cell ***cells;

size_t smemory;
