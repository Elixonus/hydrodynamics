void compute_densities(void);

extern double d0;
extern double p0;
extern double y;

void compute_pressures(void);

extern double u;
extern double *(*acceleration_external)(double r[3], double b[3]);

void compute_accelerations(void);

extern void (*integrator)(struct particle *particle, double dt);

void integrate_particles(double dt);

extern double t;
extern double dt;
extern int nt;
extern void (*initial_conditions)(void);
extern void (*boundary_conditions)(void);

void simulate_particles(int resume);
