#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <cairo.h>
#include "lib/sph.h"
#include "lib/kernels.h"
#include "lib/integrators.h"
#include "lib/simulation.h"
#include "lib/storage.h"
#include "lib/memory.h"

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#ifndef M_TAU
#define M_TAU 6.283185307
#endif

void randomize_particles(void)
{
	srand(time(NULL));
	for(int i = 0; i < pcount; i++)
	{
		struct particle *particle = &particles[i];
		particle->basic.m = 1.0 / pcount;
		for(int j = 0; j < 3; j++)
		{
			particle->basic.r[j] = ((double)(rand())) / RAND_MAX;
		}
	}
}

void update_particles_volrad(void)
{
	for(int i = 0; i < pcount; i++)
	{
		struct particle *particle = &particles[i];
		particle->volume = particle->basic.m / particle->basic.d;
		//particle->radius = cbrt(0.75 * particle->volume / M_PI);
		particle->radius = 0.05;
	}
}

void correct_particles(void)
{
	for(int i = 0; i < pcount; i++)
	{
		struct particle *particle = &particles[i];
		for(int j = 0; j < 3; j++)
		{
			if(particle->basic.r[j] < 0.0)
			{
				particle->basic.r[j] = 0.0;
			}
			else if(particle->basic.r[j] > clength * ccount[j])
			{
				particle->basic.r[j] = clength * ccount[j];
			}
		}
	}
}

double *acceleration_gravity(double r[3], double b[3])
{
	double ag[3] = {0, -0.1, 0};
	for(int j = 0; j < 3; j++)
	{
		b[j] = ag[j];
	}
	return b;
}

int width = 1000;
int height = 1000;
double zoom = 0.8;

int main(void)
{
	printf("main program started\n");

	h = 0.2;
	w = weight_cubic_spline;
	gw = gradient_weight_auto;
	lw = laplacian_weight_auto;

	pcount = 100;
	allocate_particles();

	clength = 0.1;
	ccount[0] = 10;
	ccount[1] = 10;
	ccount[2] = 1;
	allocate_cells();

	n = 100;
	allocate_sparticles();

	k = 0.001;
	d0 = 1.0;
	u = 0.0;
	t = 0.0;
	dt = 0.01;
	nt = 0;
	acceleration_external = NULL;
	integrator = integrate_euler_explicit;
	initial_conditions = randomize_particles;
	boundary_conditions = correct_particles;
	acceleration_external = acceleration_gravity;

	simulate_particles(false);
	nt = 10;

	compute_densities();/*
	for(int i = 0; i < pcount; i++)
	{
		struct particle *particle = &particles[i];
		printf("id=%d m=%f d=%f\n", particle->id, particle->basic.m, particle->basic.d);
	}*/

	/*printf("particles\n");
	for(int i = 0; i < pcount; i++)
	{
		printf("%d %f %f\n", particles[i].id, particles[i].basic.m, particles[i].basic.r[2]);
	}
	printf("cells\n");
	for(int x = 0; x < ccount[0]; x++)
	{
		for(int y = 0; y < ccount[1]; y++)
		{
			for(int z = 0; z < ccount[2]; z++)
			{
				printf("%d %f %d\n", cells[x][y][z].id, cells[x][y][z].center[1], cells[x][y][z].pcount);
			}
		}
	}*/

	for(int f = 0; f < 100; f++)
	{
		update_particles_volrad();

		printf("frame:%d\n", f);

		cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
		cairo_t *context = cairo_create(surface);

		cairo_save(context);
		cairo_translate(context, 0.0, 0.5 * ((double) height));
		cairo_scale(context, 1.0, -1.0);
		cairo_translate(context, 0.0, -0.5 * ((double) height));

		cairo_rectangle(context, 0.0, 0.0, (double) width, (double) height);
		cairo_set_source_rgb(context, 0.0, 0.0, 0.0);
		cairo_fill(context);

		cairo_save(context);
		cairo_translate(context, 0.5 * ((double) width), 0.5 * ((double) height));
		cairo_scale(context, (double) width, (double) height);
		cairo_scale(context, zoom, zoom);
		cairo_translate(context, -0.5, -0.5);

		for(int i = 0; i < pcount; i++)
		{
			struct particle *particle = &particles[i];
			cairo_arc(context, particle->basic.r[0], particle->basic.r[1], particle->radius, 0, M_TAU);
			cairo_set_source_rgb(context, 1.0, 1.0, 1.0);
			cairo_fill_preserve(context);
			cairo_set_line_width(context, 0.003);
			cairo_set_source_rgb(context, 0.0, 0.0, 0.0);
			cairo_stroke(context);
		}

		for(int x = 0; x < ccount[0]; x++)
		{
			for(int y = 0; y < ccount[1]; y++)
			{
				for(int z = 0; z < ccount[2]; z++)
				{
					struct cell *cell = &cells[x][y][z];
					cairo_rectangle(context, cell->center[0] - 0.5 * cell->length, cell->center[1] - 0.5 * cell->length, cell->length, cell->length);
					cairo_set_line_width(context, 0.003);
					cairo_set_source_rgb(context, 1.0, 1.0, 1.0);
					cairo_stroke(context);
				}
			}
		}

		cairo_restore(context);
		cairo_restore(context);

		cairo_destroy(context);
		char filename[25];
		sprintf(filename, "out/img/%05d.png", f);
		cairo_surface_write_to_png(surface, filename);
		cairo_surface_destroy(surface);

		simulate_particles(true);
	}

	deallocate_sparticles();
	deallocate_cells();
	deallocate_particles();

	return EXIT_SUCCESS;
}
