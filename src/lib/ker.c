#include <math.h>
#include "lib/sph.h"

double h;

double weight_cubic_spline(double r[3])
{

	double og = 1 / (pow(M_PI, 1.5) * h * h * h);

}

double e;

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