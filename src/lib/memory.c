#include <stdio.h>
#include <stdlib.h>
#include "storage.h"

void initialize_particle(struct particle *particle)
{
	particle->id = pid++;
	particle->radius = 0.0;
	particle->volume = 0.0;
	particle->basic.m = 0.0;
	particle->basic.d = 0.0;
	particle->basic.p = 0.0;
	for(int i = 0; i < 3; i++)
	{
		particle->basic.r[i] = 0.0;
		particle->basic.v[i] = 0.0;
		particle->a[i] = 0.0;
	}
}

void allocate_particles(void)
{
	pmemory = ((pcount > 0) ? pcount : 1) * sizeof(struct particle);
	particles = malloc(pmemory);
	if(particles == NULL)
	{
		fprintf(stderr, "error: failed to allocate particles with %dB of memory\n", (int)(pmemory));
		exit(EXIT_FAILURE);
	}
	pid = 0;
	for(int i = 0; i < pmemory / sizeof(struct particle); i++)
	{
		struct particle *particle = &particles[i];
		initialize_particle(particle);
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
			fprintf(stderr, "error: failed to reallocate particles with %dB of memory\n", (int)(pmemory));
			exit(EXIT_FAILURE);
		}
		for(int i = pcount; i < pmemory / sizeof(struct particle); i++)
		{
			struct particle *particle = &swap[i];
			initialize_particle(particle);
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
	cell->pmemory = ((cell->pcount > 0) ? cell->pcount : 1) * sizeof(struct particle *);
	cell->particles = malloc(cell->pmemory);
	if(cell->particles == NULL)
	{
		fprintf(stderr, "error: failed to allocate cell particles with %dB of memory\n", (int)(cell->pmemory));
		exit(EXIT_FAILURE);
	}
	// printf("allocated %d cell particles with %dB of memory\n", (int)(cell->pmemory / sizeof(struct particle *)), (int)(cell->pmemory));
}

void reallocate_cparticles(struct cell *cell)
{
	if(cell->pmemory <= cell->pcount * sizeof(struct particle *))
	{
		cell->pmemory = 2 * cell->pcount * sizeof(struct particle *);
		struct particle **swap = realloc(cell->particles, cell->pmemory);
		if(swap == NULL)
		{
			fprintf(stderr, "error: failed to reallocate cell particles with %dB of memory\n", (int)(cell->pmemory));
			exit(EXIT_FAILURE);
		}
		for(int i = cell->pcount; i < cell->pmemory / sizeof(struct particle *); i++)
		{
			swap[i] = NULL;
		}
		// printf("reallocated to %d cell particles with %dB of memory\n", (int)(cell->pmemory / sizeof(struct particle *)), (int)(cell->pmemory));
		cell->particles = swap;
	}
}

void deallocate_cparticles(struct cell *cell)
{
	free(cell->particles);
	// printf("deallocated %d cell particles with %dB of memory\n", (int)(cell->pmemory / sizeof(struct particle *)), (int)(cell->pmemory));
	cell->pmemory = 0;
}

void initialize_cell(struct cell *cell)
{
	cell->id = cid++;
	cell->length = clength;
	for(int i = 0; i < 3; i++)
	{
		cell->center[i] = 0.0;
	}
	cell->pcount = 0;
	cell->pmemory = 0;
	cell->particles = NULL;
}

void allocate_cells(void)
{
	cmemory[0] = ccount[0] * sizeof(struct cell **);
	cells = malloc(cmemory[0]);
	if(cells == NULL)
	{
		fprintf(stderr, "error: failed to allocate cells with %dB of memory\n", (int)(cmemory[0]));
		exit(EXIT_FAILURE);
	}
	cid = 0;
	for(int x = 0; x < ccount[0]; x++)
	{
		cmemory[1] = ccount[1] * sizeof(struct cell *);
		cells[x] = malloc(cmemory[1]);
		if(cells[x] == NULL)
		{
			fprintf(stderr, "error: failed to allocate cells with %dB of memory\n", (int)(cmemory[1]));
			exit(EXIT_FAILURE);
		}
		for(int y = 0; y < ccount[1]; y++)
		{
			cmemory[2] = ccount[2] * sizeof(struct cell);
			cells[x][y] = malloc(cmemory[2]);
			if(cells[x][y] == NULL)
			{
				fprintf(stderr, "error: failed to allocate cells with %dB of memory\n", (int)(cmemory[2]));
				exit(EXIT_FAILURE);
			}
			for(int z = 0; z < ccount[2]; z++)
			{
				struct cell *cell = &cells[x][y][z];
				initialize_cell(cell);
				cell->center[0] = ((double)(x) + 0.5) * clength;
				cell->center[1] = ((double)(y) + 0.5) * clength;
				cell->center[2] = ((double)(z) + 0.5) * clength;
				allocate_cparticles(cell);
			}
		}
	}
	printf("allocated %dx%dx%d cells with %dB of memory\n", ccount[0], ccount[1], ccount[2], (int)(cmemory[0]));
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
			free(cells[x][y]);
		}
		free(cells[x]);
	}
	free(cells);
	printf("deallocated %dx%dx%d cells with %dB of memory\n", ccount[0], ccount[1], ccount[2], (int)(cmemory[0]));
	cmemory[0] = 0;
	cmemory[1] = 0;
	cmemory[2] = 0;
}

void initialize_sparticle(struct s *si)
{
	si->m = 0.0;
	si->d = 0.0;
	si->p = 0.0;
	for(int j = 0; j < 3; j++)
	{
		si->r[j] = 0.0;
		si->v[j] = 0.0;
	}
}

void allocate_sparticles(void)
{
	smemory = ((n > 0) ? n : 1) * sizeof(struct s);
	s = malloc(smemory);
	if(s == NULL)
	{
		fprintf(stderr, "error: failed to allocate basic particles with %dB of memory\n", (int)(smemory));
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < smemory / sizeof(struct s); i++)
	{
		struct s *si = &s[i];
		initialize_sparticle(si);
	}
	printf("allocated %d basic particles with %dB of memory\n", (int)(smemory / sizeof(struct s)), (int)(smemory));
}

void reallocate_sparticles(void)
{
	if(smemory <= n * sizeof(struct s))
	{
		smemory = 2 * n * sizeof(struct s);
		struct s *swap = realloc(s, smemory);
		if(swap == NULL)
		{
			fprintf(stderr, "error: failed to reallocate basic particles with %dB of memory\n", (int)(smemory));
			exit(EXIT_FAILURE);
		}
		for(int i = n; i < smemory / sizeof(struct s); i++)
		{
			struct s *si = &swap[i];
			initialize_sparticle(si);
		}
		printf("reallocated to %d basic particles with %dB of memory\n", (int)(smemory / sizeof(struct s)), (int)(smemory));
		s = swap;
	}
}

void deallocate_sparticles(void)
{
	free(s);
	printf("deallocated %d basic particles with %dB of memory\n", (int)(smemory / sizeof(struct s)), (int)(smemory));
	smemory = 0;
}
