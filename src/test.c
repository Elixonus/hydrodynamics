#include <stdio.h>
#include <stdlib.h>
#include "lib/sph.h"
#include "lib/ker.h"


struct weight_scheme {
	double (*weight_function)(double r[3]);
	double *(*gradient_weight_function)(double r[3], double b[3]);
	double *(*laplacian_weight_function)(double r[3], double b[3]);
};

void test_weight_function(struct weight_scheme *weight_scheme)
{
	double maxk = 4.0;
	double length = 2 * maxk * h;
	double volume = 0.0;
	int nx = 100, ny = nx, nz = nx;
	double infinitesimal = (length / nx) * (length / ny) * (length / nz);

	for(int ix = 0; ix < nx; ix++)
	{
		double x = (((double) ix) / (nx - 1) - 0.5) * length;
		for(int iy = 0; iy < ny; iy++)
		{
			double y = (((double) iy) / (ny - 1) - 0.5) * length;
			for(int iz = 0; iz < nz; iz++)
			{
				double z = (((double) iz) / (nz - 1) - 0.5) * length;
				double r[3] = {x, y, z};
				double wr = weight_scheme->weight_function(r);
				volume += wr * infinitesimal;
			}
		}
	}
	printf("volume: %f\n", volume);
}

void test_weight_scheme(struct weight_scheme *weight_scheme)
{
	test_weight_function(weight_scheme);
}

int main(void)
{
	h = 1.0;
	struct weight_scheme weight_schemes[10] = {
		{weight_cubic_spline, gradient_weight_auto, laplacian_weight_auto}
	};
	test_weight_function(&weight_schemes[0]);
}
