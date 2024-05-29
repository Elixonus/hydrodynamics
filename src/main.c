#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cairo.h>
#include "lib/sph.h"
#include "lib/kernels.h"
#include "lib/integrators.h"
#include "lib/storage.h"
#include "lib/memory.h"

int main(void)
{

	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 300, 300);
	cairo_t *cr = cairo_create (surface);

	double xc = 128.0;
	double yc = 128.0;
	double radius = 100.0;
	double angle1 = 45.0  * (M_PI/180.0);
	double angle2 = 180.0 * (M_PI/180.0);

	cairo_set_line_width (cr, 10.0);
	cairo_arc (cr, xc, yc, radius, angle1, angle2);
	cairo_stroke (cr);

	cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
	cairo_set_line_width (cr, 6.0);

	cairo_arc (cr, xc, yc, 10.0, 0, 2*M_PI);
	cairo_fill (cr);

	cairo_arc (cr, xc, yc, radius, angle1, angle1);
	cairo_line_to (cr, xc, yc);
	cairo_arc (cr, xc, yc, radius, angle2, angle2);
	cairo_line_to (cr, xc, yc);
	cairo_stroke (cr);

	cairo_surface_write_to_png (surface, "example.png");
	cairo_destroy (cr);
	cairo_surface_destroy (surface);

	return EXIT_SUCCESS;
}
