#ifndef SIMULATION_H
#define SIMULATION_H

extern double clength;

void partition_particles(void);

void compute_densities(void);

extern double d0;
extern double k;

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

#endif
