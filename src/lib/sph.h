struct s {
	double m;
	double d;
	double p;
	double r[3];
	double v[3];
};

int n;
struct s *s;

double (*w)(double r[3]);
double *(*gw)(double r[3], double b[3]);
double *(*lw)(double r[3], double b[3]);

double d(double r[3]);
double p(double r[3]);
double *v(double r[3], double b[3]);
double *gp(double r[3], double b[3]);
double *lv(double r[3], double b[3]);
