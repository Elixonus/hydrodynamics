#include <math.h>

struct particle
{
	double mass;
	double density;
	double pressure;
	double position[2];
	double velocity[2];
};

double fdensity(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double point[2])
)
{
	double density = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int a = 0; a < 2; a++)
			displacement[a] = point[a] - particles[p]->position[a];
		double weight = weightf(displacement);
		density += particles[p]->mass * weight;
	}
	return density;
}

double fpressure(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double point[2])
)
{
	double pressure = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int a = 0; a < 2; a++)
			displacement[a] = point[a] - particles[p]->position[a];
		double weight = weightf(displacement);
		pressure += (
			particles[p]->mass *
			particles[p]->pressure /
			particles[p]->density
		) * weight;
	}
	return pressure;
}

double *fvelocity(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double point[2]),
	double velocity[2]
)
{
	for(int a = 0; a < 2; a++) velocity[a] = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int a = 0; a < 2; a++)
			displacement[a] = point[a] - particles[p]->position[a];
		double weight = weightf(displacement);
		for(int a = 0; a < 2; a++)
			velocity[a] += (
				particles[p]->mass *
				particles[p]->velocity[a] /
				particles[p]->density
			) * weight;
	}
}

double *fpressureg(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double point[2]),
	double *(*weightgf)(double point[2], double weightg[2]),
	double pressureg[2]
)
{
	double density = fdensity(count, particles, point, weightf);
	double pressure = fpressure(count, particles, point, weightf);
	for(int a = 0; a < 2; a++) pressureg[a] = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int a = 0; a < 2; a++)
			displacement[a] = point[a] - particles[p]->position[a];
		double weightg[2];
		weightgf(displacement, weightg);
		for(int a = 0; a < 2; a++)
			pressureg[a] += particles[p]->mass * (
				particles[p]->pressure / particles[p]->density *
				density / particles[p]->density +
				pressure / density
			) * weightg[a];
	}
}

double *fvelocityl(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double point[2]),
	double *(*weightlf)(double point[2], double weightl[2]),
	double velocityl[2]
)
{
	double velocity[2];
	fvelocity(count, particles, point, weightf, velocity);
	for(int a = 0; a < 2; a++) velocityl[a] = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int a = 0; a < 2; a++)
			displacement[a] = point[a] - particles[p]->position[a];
		double weightl[2];
		weightlf(displacement, weightl);
		for(int a = 0; a < 2; a++)
			velocityl[a] += (
				particles[p]->mass *
				(particles[p]->velocity[a] - velocity[a]) /
				particles[p]->density
			) * weightl[a];
	}
}
