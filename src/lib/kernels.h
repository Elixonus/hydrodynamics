extern double h;
extern double e;

double weight_gaussian(double r[3]);

double weight_cubic_spline(double r[3]);

double *gradient_weight_auto(double r[3], double b[3]);

double *laplacian_weight_auto(double r[3], double b[3]);
