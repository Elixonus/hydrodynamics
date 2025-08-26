#include <math.h>

#ifdef SPHAXES

struct particle
{
	double mass;
	double density;
	double pressure;
	double position[SPHAXES];
	double velocity[SPHAXES];
};

double sdensity(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double radius)
)
{
	double density = 0.0;
	for(int p = 0; p < count; p++)
	{
		double radius = 0.0;
		for(int a = 0; a < SPHAXES; a++)
			radius += pow(point[a] - particles[p]->position[a], 2.0);
		radius = sqrt(radius);
		double weight = weightf(radius);
		density += particles[p]->mass * weight;
	}
	return density;
}

double spressure(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double radius)
)
{
	double pressure = 0.0;
	for(int p = 0; p < count; p++)
	{
		double radius = 0.0;
		for(int a = 0; a < SPHAXES; a++)
			radius += pow(point[a] - particles[p]->position[a], 2.0);
		radius = sqrt(radius);
		double weight = weightf(radius);
		pressure += (
			particles[p]->mass *
			particles[p]->pressure /
			particles[p]->density
		) * weight;
	}
	return pressure;
}

void svelocity(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double radius),
	double result[SPHAXES]
)
{
	double velocity[SPHAXES];
	for(int a = 0; a < SPHAXES; a++) velocity[a] = 0.0;
	for(int p = 0; p < count; p++)
	{
		double radius = 0.0;
		for(int a = 0; a < SPHAXES; a++)
			radius += pow(point[a] - particles[p]->position[a], 2.0);
		radius = sqrt(radius);
		double weight = weightf(radius);
		for(int a = 0; a < SPHAXES; a++)
			velocity[a] += (
				particles[p]->mass *
				particles[p]->velocity[a] /
				particles[p]->density
			) * weight;
	}
	for(int a = 0; a < SPHAXES; a++)
		result[a] = velocity[a];
}

void spressureg(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double radius),
	void (*weightgf)(double radius, double result[SPHAXES]),
	double result[SPHAXES]
)
{
	double density = sdensity(particles, count, point, weightf);
	double pressure = spressure(particles, count, point, weightf);
	double pressureg[SPHAXES];
	for(int a = 0; a < SPHAXES; a++) pressureg[a] = 0.0;
	for(int p = 0; p < count; p++)
	{
		double radius = 0.0;
		for(int a = 0; a < SPHAXES; a++)
			radius += pow(point[a] - particles[p]->position[a], 2.0);
		radius = sqrt(radius);
		double weightg[SPHAXES];
		weightgf(radius, weightg);
		for(int a = 0; a < SPHAXES; a++)
			pressureg[a] += particles[p]->mass * (
				particles[p]->pressure / particles[p]->density *
				density / particles[p]->density +
				pressure / density
			) * weightg[a];
	}
	for(int a = 0; a < SPHAXES; a++)
		result[a] = pressureg[a];
}

void svelocityl(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double radius),
	void (*weightlf)(double radius, double result[SPHAXES]),
	double result[SPHAXES]
)
{
	double velocity[SPHAXES];
	svelocity(particles, count, point, weightf, velocity);
	double velocityl[SPHAXES];
	for(int a = 0; a < SPHAXES; a++) velocityl[a] = 0.0;
	for(int p = 0; p < count; p++)
	{
		double radius = 0.0;
		for(int a = 0; a < SPHAXES; a++)
			radius += pow(point[a] - particles[p]->position[a], 2.0);
		radius = sqrt(radius);
		double weightl[SPHAXES];
		weightlf(radius, weightl);
		for(int a = 0; a < SPHAXES; a++)
			velocityl[a] += (
				particles[p]->mass *
				(particles[p]->velocity[a] - velocity[a]) /
				particles[p]->density
			) * weightl[a];
	}
	for(int a = 0; a < SPHAXES; a++)
		result[a] = velocityl[a];
}

#endif
