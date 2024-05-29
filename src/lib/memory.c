#include <stdio.h>
#include <stdlib.h>
#include "storage.h"

void allocate_particles(void)
{
	pmemory = pcount * sizeof(struct particle);
	particles = malloc(pmemory);
	if(particles == NULL)
	{
		fprintf(stderr, "failed to allocate particles with %dB of memory\n", (int)(pmemory));
		exit(EXIT_FAILURE);
	}
	printf("allocated %d particles with %dB of memory\n", (int)(pmemory / sizeof(struct particle)), (int)(pmemory));
}

void reallocate_particles(void)
{
	if(pmemory <= pcount * sizeof(struct particle))
	{
		pmemory = 2 * pcount * sizeof(struct particle);
		struct particle *swap = realloc(particles, pmemory);
		if(swap == NULL)
		{
			fprintf(stderr, "failed to reallocate particles with %dB of memory\n", (int)(pmemory));
			exit(EXIT_FAILURE);
		}
		printf("reallocated to %d particles with %dB of memory\n", (int)(pmemory / sizeof(struct particle)), (int)(pmemory));
		particles = swap;
	}
}

void deallocate_particles(void)
{
	free(particles);
	printf("deallocated %d particles with %dB of memory\n", (int)(pmemory / sizeof(struct particle)), (int)(pmemory));
	pmemory = 0;
}

void allocate_cparticles(struct cell *cell)
{
	cell->pmemory = cell->pcount * sizeof(struct particle *);
	cell->particles = malloc(cell->pmemory);
	if(cell->particles == NULL)
	{
		fprintf(stderr, "failed to allocate cell particles with %dB of memory\n", (int)(cell->pmemory));
		exit(EXIT_FAILURE);
	}
	printf("allocated %d cell particles with %dB of memory\n", (int)(cell->pmemory / sizeof(struct particle *)), (int)(cell->pmemory));
}

void reallocate_cparticles(struct cell *cell)
{
	if(cell->pmemory <= cell->pcount * sizeof(struct particle *))
	{
		cell->pmemory = 2 * cell->pcount * sizeof(struct particle *);
		struct particle **swap = realloc(cell->particles, cell->pmemory);
		if(swap == NULL)
		{
			fprintf(stderr, "failed to reallocate cell particles with %dB of memory\n", (int)(cell->pmemory));
			exit(EXIT_FAILURE);
		}
		printf("reallocated to %d cell particles with %dB of memory\n", (int)(cell->pmemory / sizeof(struct particle *)), (int)(cell->pmemory));
		cell->particles = swap;
	}
}

void deallocate_cparticles(struct cell *cell)
{
	free(cell->particles);
	printf("deallocated %d cell particles with %dB of memory\n", (int)(cell->pmemory / sizeof(struct particle *)), (int)(cell->pmemory));
	cell->pmemory = 0;
}

void allocate_cells(void)
{
	cmemory = ccount[0] * ccount[1] * ccount[2] * sizeof(struct cell);
	cells = malloc(cmemory);
	if(cells == NULL)
	{
		fprintf(stderr, "failed to allocate cells with %dB of memory\n", (int)(cmemory));
		exit(EXIT_FAILURE);
	}
	for(int x = 0; x < ccount[0]; x++)
	{
		for(int y = 0; y < ccount[1]; y++)
		{
			for(int z = 0; z < ccount[2]; z++)
			{
				struct cell *cell = &cells[x][y][z];
				allocate_cparticles(cell);
			}
		}
	}
	printf("allocated %dx%dx%d cells with %dB of memory\n", ccount[0], ccount[1], ccount[2], (int)(cmemory));
}

void deallocate_cells(void)
{
	for(int x = 0; x < ccount[0]; x++)
	{
		for(int y = 0; y < ccount[1]; y++)
		{
			for(int z = 0; z < ccount[2]; z++)
			{
				struct cell *cell = &cells[x][y][z];
				deallocate_cparticles(cell);
			}
		}
	}

	free(cells);
	printf("deallocated %dx%dx%d cells with %dB of memory\n", ccount[0], ccount[1], ccount[2], (int)(cmemory));
	cmemory = 0;
}
