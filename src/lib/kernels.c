#include <stdio.h>
#include <math.h>
#include "sph.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double h;

double weight_cubic_spline(double r[3])
{
	double o3 = 1.0 / (M_PI * pow(h, 3.0));
	double mr = sqrt(pow(r[0], 2.0) + pow(r[1], 2.0) + pow(r[2], 2.0));
	double q = mr / h;
	double wr;
	if(q < 1.0)
	{
		wr = 1.0 - 1.5 * pow(q, 2.0) + 0.75 * pow(q, 3.0);
	}
	else if(q < 2.0)
	{
		wr = 0.25 * pow((2.0 - q), 3.0);
	}
	else
	{
		wr = 0.0;
	}
	wr *= o3;
	return wr;
}

double weight_gaussian(double r[3])
{
	double og = 1.0 / (pow(M_PI, 1.5) * pow(h, 3.0));
	double mr = sqrt(pow(r[0], 2.0) + pow(r[1], 2.0) + pow(r[2], 2.0));
	double q = mr / h;
	double wr;
	if(q < 3.0)
	{
		wr = og * exp(-pow(q, 2.0));
	}
	else
	{
		wr = 0.0;
	}
	return wr;
}

double weight_poly6(double r[3])
{
	double og = 315.0 / (64.0 * M_PI * pow(h, 9.0));
	double mr = sqrt(pow(r[0], 2.0) + pow(r[1], 2.0) + pow(r[2], 2.0));
	double wr;
	if(mr <= h)
	{
		wr = pow(pow(h, 2.0) - pow(mr, 2.0), 3.0);
	}
	else
	{
		wr = 0.0;
	}
	wr *= og;
	return wr;
}

double weight_spiky(double r[3])
{
	double og = 15.0 / (M_PI * pow(h, 6.0));
	double mr = sqrt(pow(r[0], 2.0) + pow(r[1], 2.0) + pow(r[2], 2.0));
	double wr;
	if(mr < h)
	{
		wr = pow(h - mr, 3.0);
	}
	else
	{
		wr = 0.0;
	}
	wr *= og;
	return wr;
}

double weight_viscous(double r[3])
{
	double og = 15.0 / (2.0 * M_PI * pow(h, 3.0));
	double mr = sqrt(pow(r[0], 2.0) + pow(r[1], 2.0) + pow(r[2], 2.0));
	double wr;
	if(mr < h)
	{
		wr = 0.0 - pow(mr, 3.0) / (2.0 * pow(h, 3.0)) - pow(mr, 2.0) / (2.0 * pow(h, 2.0)) + h / (2.0 * mr) - 1.0;
	}
	else
	{
		wr = 0.0;
	}
	wr *= og;
	return wr;
}

double e = 1e-6;

double ce(int c)
{
	double ced = 0.0;
	if(c % 3 == 0)
	{
		ced = 1.0;
	}
	return ced;
}

double *gradient_weight_auto(double r[3], double b[3])
{
	double gwr[3];
	for(int i = 0; i < 3; i++)
	{
		double res[2][3];
		for(int j = 0; j < 3; j++)
		{
			res[0][j] = r[j] + e * ce(i - j);
			res[1][j] = r[j] - e * ce(i - j);
		}
		gwr[i] = (w(res[0]) - w(res[1])) / (2 * e);
	}
	for(int c = 0; c < 3; c++)
	{
		b[c] = gwr[c];
	}
	return b;
}

double *laplacian_weight_auto(double r[3], double b[3])
{
	double lwr[3];
	for(int i = 0; i < 3; i++)
	{
		double res[2][3];
		for(int j = 0; j < 3; j++)
		{
			res[0][j] = r[j] + e * ce(i - j);
			res[1][j] = r[j] - e * ce(i - j);
		}
		lwr[i] = (w(res[0]) - 2 * w(r) + w(res[1])) / (e * e);
	}
	for(int c = 0; c < 3; c++)
	{
		b[c] = lwr[c];
	}
	return b;
}
