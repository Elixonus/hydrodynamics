#include <stdio.h>
#include <math.h>
#include "sph.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double h;

double weight_cubic_spline(double r[3])
{
	double o3 = 1.0 / (M_PI * h * h * h);
	double ru = sqrt(pow(r[0], 2) + pow(r[1], 2) + pow(r[2], 2));
	double wr;

	if(ru < h)
	{
		wr = 1.0 - 1.5 * pow(ru / h, 2) + 0.75 * pow(ru / h, 3);
	}
	else if(ru < 2.0 * h)
	{
		wr = 0.25 * pow((2 - ru / h), 3);
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
	double og = 1.0 / (pow(M_PI, 1.5) * pow(h, 3));
	double ru = sqrt(pow(r[0], 2) + pow(r[1], 2) + pow(r[2], 2));
	double q = ru / h;
	double wr;

	if(q < 3)
	{
		wr = og * exp(-pow(q, 2));
	}
	else
	{
		wr = 0.0;
	}

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
