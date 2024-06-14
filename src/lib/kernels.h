#ifndef KERNELS_H
#define KERNELS_H

extern double h;

double weight_cubic_spline(double r[3]);

double weight_gaussian(double r[3]);

double weight_poly6(double r[3]);

double weight_spiky(double r[3]);

extern double e;

double *gradient_weight_auto(double r[3], double b[3]);

double *laplacian_weight_auto(double r[3], double b[3]);

#endif
