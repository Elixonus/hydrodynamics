#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sph.h"
#include "storage.h"
#include "memory.h"
#include "kernels.h"
#include "integrators.h"



void compute_densities(void)
{
	for(int i = 0; i < n; i++)
	{
		double dr = d(s[i].r);
		s[i].d = dr;
	}
}

double d0;
double p0;
double y;

void compute_pressures(void)
{
	for(int i = 0; i < n; i++)
	{
		double dr = s[i].d;
		double pr = p0 * (pow(dr / d0, y) - 1);
		s[i].p = pr;
	}
}

double u;
double *(*acceleration_external)(double r[3], double b[3]);

void compute_acceleration(void)
{
	for(int i = 0; i < n; i++)
	{
		double gpr[3];
		gp(s[i].r, gpr);
		double lvr[3];
		lv(s[i].r, lvr);
		double aer[3];
		acceleration_external(s[i].r, aer);
		for(int j = 0; j < 3; j++)
		{
			a[i][j] = aer[j] - gpr[j] / s[i].d + lvr[j] * u / s[i].d;
		}
	}
}


void (*integrator)(struct particle *, double dt);

void integrate_particles(double dt)
{
	for(int i = 0; i < n; i++)
}

double t;
double dt;
int nt;
void (*initial_conditions)(void);
void (*boundary_conditions)(void);
