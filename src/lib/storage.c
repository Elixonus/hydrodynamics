#include <stdlib.h>
#include "sph.h"

struct particle {
	int id;
	double color[3];
	double radius;
	double volume;
	struct s basic;
	double a[3];
};

struct cell {
	int id;
	double length;
	double position[3];
	int pcount;
	size_t pmemory;
	struct particle **particles;
};

int pid = 0;
int pcount;
size_t pmemory;
struct particle *particles;

int cid = 0;
int ccount[3];
size_t cmemory;
struct cell ***cells;

size_t smemory;