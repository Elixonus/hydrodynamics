#include <stdio.h>

struct s {
	double m;
	double d;
	double p;
	double r[3];
	double v[3];
};

int n;
struct s *s;

double (*w)(double[3]);
double *(*gw)(double[3], double[3]);
double *(*lw)(double[3], double[3]);

double d(double r[3])
{
	double dr = 0.0;
	for(int i = 0; i < n; i++)
	{
		double rw[3];
		for(int c = 0; c < 3; c++)
		{
			rw[c] = r[c] - s[i].r[c];
		}
		double wr = w(rw);
		dr += s[i].m * wr;
	}
	return dr;
}

double p(double r[3])
{
	double pr = 0.0;
	for(int i = 0; i < n; i++)
	{
		double rw[3];
		for(int c = 0; c < 3; c++)
		{
			rw[c] = r[c] - s[i].r[c];
		}
		double wr = w(rw);
		pr += s[i].m * s[i].p / s[i].d * wr;
	}
	return pr;
}

double *v(double r[3], double b[3])
{
	double vr[3] = {0.0, 0.0, 0.0};
	for(int i = 0; i < n; i++)
	{
		double rw[3];
		for(int c = 0; c < 3; c++)
		{
			rw[c] = r[c] - s[i].r[c];
		}
		double wr = w(rw);
		for(int c = 0; c < 3; c++)
		{
			vr[c] += s[i].m * s[i].v[c] / s[i].d;
		}
	}
	for(int c = 0; c < 3; c++)
	{
		b[c] = vr[c];
	}
	printf("hi: \n");
	return b;
}

double *gp(double r[3], double b[3])
{
	double dr = d(r);
	double pr = p(r);
	double gpr[3] = {0.0, 0.0, 0.0};
	for(int i = 0; i < n; i++)
	{
		double rw[3];
		for(int c = 0; c < 3; c++)
		{
			rw[c] = r[c] - s[i].r[c];
		}
		double gwr[3];
		gw(rw, gwr);
		for(int c = 0; c < 3; c++)
		{
			gpr[c] += s[i].m * (s[i].p / s[i].d * dr / s[i].d + pr / dr) * gwr[c];
		}
	}
	for(int c = 0; c < 3; c++)
	{
		b[c] = gpr[c];
	}
	return b;
}

double *lv(double r[3], double b[3])
{
	double vr[3];
	v(r, vr);
	double lvr[3] = {0.0, 0.0, 0.0};
	for(int i = 0; i < n; i++)
	{
		double rw[3];
		for(int c = 0; c < 3; c++)
		{
			rw[c] = r[c] - s[i].r[c];
		}
		double lwr[3];
		lw(rw, lwr);
		for(int c = 0; c < 3; c++)
		{
			lvr[c] += s[i].m * (s[i].v[c] - vr[c]) / s[i].d * lwr[c];
		}
	}
	for(int c = 0; c < 3; c++)
	{
		b[c] = lvr[c];
	}
	return b;
}

