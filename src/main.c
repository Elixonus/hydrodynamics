#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cairo.h>
#include "lib/sph.h"
#include "lib/kernels.h"
#include "lib/integrators.h"
#include "lib/storage.h"
#include "lib/memory.h"

#define M_PI 3.14159265

int main(void)
{
	printf("main program started\n");

	pcount = 100;
	allocate_particles();

	clength = 1.0;
	ccount[0] = 10;
	ccount[1] = 10;
	ccount[2] = 1;
	allocate_cells();

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

	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 300, 300);
	cairo_t *context = cairo_create(surface);

	double xc = 128.0;
	double yc = 128.0;
	double radius = 100.0;
	double angle1 = 45.0  * (M_PI/180.0);
	double angle2 = 180.0 * (M_PI/180.0);

	cairo_set_line_width(context, 10.0);
	cairo_arc(context, xc, yc, radius, angle1, angle2);
	cairo_stroke(context);

	cairo_set_source_rgba(context, 1, 0.2, 0.2, 0.6);
	cairo_set_line_width(context, 6.0);

	cairo_arc(context, xc, yc, 10.0, 0, 2*M_PI);
	cairo_fill(context);

	cairo_arc(context, xc, yc, radius, angle1, angle1);
	cairo_line_to(context, xc, yc);
	cairo_arc(context, xc, yc, radius, angle2, angle2);
	cairo_line_to(context, xc, yc);
	cairo_stroke(context);

	cairo_surface_write_to_png (surface, "example.png");
	cairo_destroy(context);
	cairo_surface_destroy(surface);

	return EXIT_SUCCESS;
}
