#include <math.h>

struct particle
{
	double mass;
	double density;
	double pressure;
	double position[2];
	double velocity[2];
}

double densityp(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double[2])
)
{
	double density = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int c = 0; c < 2; c++)
		{
			displacement[c] = point[c] - particles[p]->position[c];
		}
		double weight = weightf(displacement);
		density += particles[p]->m[c] * weight;
	}
	return density;
}

double pressurep(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double[2])
)
{
	double pressure = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int c = 0; c < 2; c++)
		{
			displacement[c] = point[c] - particles[p]->position[c];
		}
		double weight = weightf(displacement);
		pressure += (
			particles[p]->mass * particles[p]->pressure /
			particles[p]->density * weight
		);
	}
	return pressure;
}

double *velocityp(
	int count,
	struct particle **particles,
	double point[2],
	double (*weightf)(double[2]),
	double buffer[2]
)
{
	double velocity[2] = {0.0, 0.0};
	for(int p = 0; p < count; p++)
	{
		double displacement[2];
		for(int c = 0; c < 2; c++)
		{
			displacement[c] = point[c] - particles[p]->position[c];
		}
		double weight = weightf(displacement);
		for(int c = 0; c < 2; c++)
		{
			velocity[c] += (
				particles[p]->mass * particles[p]->velocity /
				particles[p]->density * weight
			);
		}
	}
	for(int c = 0; c < 2; c++)
	{
		buffer[c] = velocity[c];
	}
	return buffer;
}

