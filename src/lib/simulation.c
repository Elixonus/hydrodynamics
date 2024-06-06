#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "sph.h"
#include "kernels.h"
#include "integrators.h"
#include "storage.h"
#include "memory.h"



void partition_particles(void)
{
	for(int x = 0; x < ccount[0]; x++)
	{
		for(int y = 0; y < ccount[1]; y++)
		{
			for(int z = 0; z < ccount[2]; z++)
			{
				struct cell *cell = &cells[x][y][z];
				cell->pcount = 0;
			}
		}
	}

	for(int i = 0; i < pcount; i++)
	{
		int c[3];
		for(int j = 0; j < 3; j++)
		{
			c[j] = (int)(floor(particles[i].basic.r[j] / clength));

			if(c[j] < 0)
			{
				c[j] = 0;
			}
			else if(c[j] >= ccount[j])
			{
				c[j] = ccount[j] - 1;
			}
		}

		struct cell *cell = &cells[c[0]][c[1]][c[2]];
		reallocate_cparticles(cell);
		cell->particles[cell->pcount] = &particles[i];
		cell->pcount++;
	}
}

void prepare_particles(struct cell *cell)
{
	// temporary implementation, should take into account neighbors as well later.
	n = cell->pcount;
	printf("cell->pcount = %d\n", n);
	reallocate_sparticles();
	for(int i = 0; i < cell->pcount; i++)
	{
		s[i] = cell->particles[i]->basic;
	}
}

void compute_densities(void)
{
	for(int x = 0; x < ccount[0]; x++)
	{
		for(int y = 0; y < ccount[1]; y++)
		{
			for(int z = 0; z < ccount[2]; z++)
			{
				struct cell *cell = &cells[x][y][z];
				prepare_particles(cell);

				for(int i = 0; i < cell->pcount; i++)
				{
					struct particle *particle = cell->particles[i];
					double dr = d(particle->basic.r);
					particle->basic.d = dr;
				}
			}
		}
	}
}

double d0;
double k;

void compute_pressures(void)
{
	for(int x = 0; x < ccount[0]; x++)
	{
		for(int y = 0; y < ccount[1]; y++)
		{
			for(int z = 0; z < ccount[2]; z++)
			{
				struct cell *cell = &cells[x][y][z];
				prepare_particles(cell);

				for(int i = 0; i < cell->pcount; i++)
				{
					struct particle *particle = cell->particles[i];
					double dr = particle->basic.d;
					double pr = k * (dr - d0);
					particle->basic.p = pr;
				}
			}
		}
	}
}

double u;
double *(*acceleration_external)(double r[3], double b[3]);

void compute_accelerations(void)
{
	for(int x = 0; x < ccount[0]; x++)
	{
		for(int y = 0; y < ccount[1]; y++)
		{
			for(int z = 0; z < ccount[2]; z++)
			{
				struct cell *cell = &cells[x][y][z];
				prepare_particles(cell);

				for(int i = 0; i < cell->pcount; i++)
				{
					struct particle *particle = cell->particles[i];
					double gpr[3];
					gp(particle->basic.r, gpr);
					double lvr[3];
					lv(particle->basic.r, lvr);
					double aer[3] = {0.0, 0.0, 0.0};
					if(acceleration_external != NULL)
					{
						acceleration_external(particle->basic.r, aer);
					}
					for(int j = 0; j < 3; j++)
					{
						particle->a[j] = aer[j] - gpr[j] / particle->basic.d + lvr[j] * u / particle->basic.d;
					}
				}
			}
		}
	}
}

void (*integrator)(struct particle *particle, double dt);

void integrate_particles(double dt)
{
	for(int i = 0; i < pcount; i++)
	{
		integrator(&particles[i], dt);
	}
}

double t;
double dt;
int nt;
void (*initial_conditions)(void);
void (*boundary_conditions)(void);

void simulate_particles(bool resume)
{
	if(resume == false)
	{
		t = 0.0;
		if(initial_conditions != NULL)
		{
			initial_conditions();
		}
	}
	for(int it = 0; it < nt; it++)
	{
		partition_particles();
		compute_densities();
		/*compute_pressures();
		compute_accelerations();
		integrate_particles(dt);
		t += dt;
		if(boundary_conditions != NULL)
		{
			boundary_conditions();
		}*/
	}
}
