#include <math.h>

struct particle
{
	double mass;
	double density;
	double pressure;
	double position[2];
	double velocity[2];
};

double pdensity(
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
		for(int c = 0; c < 2; c++)
			displacement[c] = point[c] - particles[p]->position[c];
		double weight = weightf(displacement);
		density += particles[p]->mass * weight;
	}
	return density;
}

double ppressure(
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
		for(int c = 0; c < 2; c++)
			displacement[c] = point[c] - particles[p]->position[c];
		double weight = weightf(displacement);
		pressure += (
			particles[p]->mass *
			particles[p]->pressure /
			particles[p]->density
		) * weight;
	}
	return pressure;
}

double *pvelocity(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double point[2]),
	double buffer[2]
)
{
	double velocity[2] = {0.0, 0.0};
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int c = 0; c < 2; c++)
			displacement[c] = point[c] - particles[p]->position[c];
		double weight = weightf(displacement);
		for(int c = 0; c < 2; c++)
			velocity[c] += (
				particles[p]->mass *
				particles[p]->velocity[c] /
				particles[p]->density
			) * weight;
	}
	for(int c = 0; c < 2; c++)
		buffer[c] = velocity[c];
	return buffer;
}

double *ppressureg(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double point[2]),
	double *(*weightgf)(double point[2], double buffer[2]),
	double buffer[2]
)
{
	double density = pdensity(count, particles, point, weightf);
	double pressure = ppressure(count, particles, point, weightf);
	double pressureg[2] = {0.0, 0.0};
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int c = 0; c < 2; c++)
			displacement[c] = point[c] - particles[p]->position[c];
		double weightg[2];
		weightgf(displacement, weightg);
		for(int c = 0; c < 2; c++)
			pressureg[c] += particles[p]->mass * (
				particles[p]->pressure / particles[p]->density *
				density / particles[p]->density +
				pressure / density
			) * weightg[c];
	}
	for(int c = 0; c < 2; c++)
		buffer[c] = pressureg[c];
	return buffer;
}

double *pvelocityl(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double point[2]),
	double *(*weightlf)(double point[2], double buffer[2]),
	double buffer[2]
)
{
	double velocity[2];
	pvelocity(count, particles, point, weightf, velocity);
	double velocityl[2] = {0.0, 0.0};
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int c = 0; c < 2; c++)
			displacement[c] = point[c] - particles[p]->position[c];
		double weightl[2];
		weightlf(displacement, weightl);
		for(int c = 0; c < 2; c++)
			velocityl[c] += (
				particles[p]->mass *
				(particles[p]->velocity[c] - velocity[c]) /
				particles[p]->density
			) * weightl[c];
	}
	for(int c = 0; c < 2; c++)
		buffer[c] = velocityl[c];
	return buffer;
}
