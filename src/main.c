#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cairo.h>
#include "lib/sph.h"
#include "lib/kernels.h"
#include "lib/integrators.h"
#include "lib/storage.h"
#include "lib/memory.h"

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#ifndef M_TAU
#define M_TAU 6.283185307
#endif


void initial_conditions(void)
{
	srand(time(NULL));
	for(int i = 0; i < pcount; i++)
	{
		struct particle *particle = particles[i];
		for(int j = 0; j < 3; j++)
		{
			particles[i].basic.m = 1.0;
			particles[i].basic.d = 1.0;
			particles[i].basic.r[j] = ((double)(rand())) / RAND_MAX;
			particles[i].volume = ;
		}
	}
}


int main(void)
{
	printf("main program started\n");

	pcount = 100;
	allocate_particles();

	clength = 0.1;
	ccount[0] = 10;
	ccount[1] = 10;
	ccount[2] = 1;
	allocate_cells();

	initial_conditions();

	printf("particles\n");
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
	}

	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 1000, 1000);
	cairo_t *context = cairo_create(surface);

	cairo_save(context);
	cairo_translate(context, 0.0, 500.0);
	cairo_scale(context, 1.0, -1.0);
	cairo_translate(context, 0.0, -500.0);

	cairo_rectangle(context, 0.0, 0.0, 1000.0, 1000.0);
	cairo_set_source_rgb(context, 0.0, 0.0, 0.0);
	cairo_fill(context);

	cairo_save(context);
	cairo_translate(context, 500.0, 500.0);
	cairo_scale(context, 800.0, 800.0);
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
	cairo_surface_write_to_png (surface, "example.png");
	cairo_surface_destroy(surface);

	return EXIT_SUCCESS;
}
