#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib/sph.h"
#include "lib/kernels.h"


struct weight_scheme {
	double (*weight_function)(double r[3]);
	double *(*gradient_weight_function)(double r[3], double b[3]);
	double *(*laplacian_weight_function)(double r[3], double b[3]);
	char *function_names[3];
};

void test_weight_function(double (*weight_function)(double r[3]), char *function_name)
{
	printf("weight function: %s (integrating kernel across volume (should add up to 1))\n", function_name);

	double average = 0.0;
	double maxk = 5.0;
	int nh = 10;

	for(int ih = 0; ih < nh; ih++)
	{
		h = pow(10, 3.0 * ((int) ih) / (nh - 1) - 2.0); // 0.01 to 10
		double length = 2 * maxk * h;
		int nx = 100, ny = nx, nz = nx;
		double infinitesimal = (length / nx) * (length / ny) * (length / nz);
		double volume = 0.0;

		for(int ix = 0; ix < nx; ix++)
		{
			double x = (((double) ix) / nx - 0.5) * length;
			for(int iy = 0; iy < ny; iy++)
			{
				double y = (((double) iy) / ny - 0.5) * length;
				for(int iz = 0; iz < nz; iz++)
				{
					double z = (((double) iz) / nz - 0.5) * length;
					double r[3] = {x, y, z};
					double wr = weight_function(r);
					// printf("h: %f, wr: %f, r: <%f, %f, %f>\n", h, wr, r[0], r[1], r[2]);
					volume += wr * infinitesimal;
				}
			}
		}

		average += volume / nh;
	}

	printf("volume (avg) = %lf\n", average);
}

void test_gradient_weight_function(double *(*gradient_weight_function)(double r[3], double b[3]), char *function_name)
{
	double maxk = 5.0;
	int nh = 10;

	for(int ih = 0; ih < nh; ih++)
	{
		h = pow(10, 3.0 * ((int) ih) / (nh - 1) - 2.0); // 0.01 to 10
		double length = 2 * maxk * h;
		int nx = 100, ny = nx, nz = nx;
		double infinitesimal = (length / nx) * (length / ny) * (length / nz);
		double volume = 0.0;

		for(int ix = 0; ix < nx; ix++)
		{
			double x = (((double) ix) / nx - 0.5) * length;
			for(int iy = 0; iy < ny; iy++)
			{
				double y = (((double) iy) / ny - 0.5) * length;
				for(int iz = 0; iz < nz; iz++)
				{
					double z = (((double) iz) / nz - 0.5) * length;
					double r[3] = {x, y, z};
					double gwr = weight_function(r);
					// printf("h: %f, wr: %f, r: <%f, %f, %f>\n", h, wr, r[0], r[1], r[2]);
					volume += wr * infinitesimal;
				}
			}
		}
}

void test_weight_scheme(struct weight_scheme *weight_scheme)
{
	printf("weight scheme: (%s, %s, %s)\n", weight_scheme->function_names[0], weight_scheme->function_names[1], weight_scheme->function_names[2]);
	test_weight_function(weight_scheme->weight_function, weight_scheme->function_names[0]);
}

int main(void)
{
	struct weight_scheme weight_schemes[10] = {
		{weight_cubic_spline, gradient_weight_auto, laplacian_weight_auto, {"cubic spline", "auto gradient", "auto laplacian"}}
	};
	test_weight_scheme(&weight_schemes[0]);
}
