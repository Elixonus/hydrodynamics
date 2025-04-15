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
	double (*weightf)(double point[SPHAXES])
)
{
	double density = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[SPHAXES];
		for(int a = 0; a < SPHAXES; a++)
			displacement[a] = point[a] - particles[p]->position[a];
		double weight = weightf(displacement);
		density += particles[p]->mass * weight;
	}
	return density;
}

double spressure(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double point[SPHAXES])
)
{
	double pressure = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[SPHAXES];
		for(int a = 0; a < SPHAXES; a++)
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

void svelocity(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double velocity[SPHAXES],
	double (*weightf)(double point[SPHAXES])
)
{
	for(int a = 0; a < SPHAXES; a++) velocity[a] = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[SPHAXES];
		for(int a = 0; a < SPHAXES; a++)
			displacement[a] = point[a] - particles[p]->position[a];
		double weight = weightf(displacement);
		for(int a = 0; a < SPHAXES; a++)
			velocity[a] += (
				particles[p]->mass *
				particles[p]->velocity[a] /
				particles[p]->density
			) * weight;
	}
}

void spressureg(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double pressureg[SPHAXES],
	double (*weightf)(double point[SPHAXES]),
	void (*weightgf)(double point[SPHAXES], double weightg[SPHAXES])
)
{
	double density = sdensity(particles, count, point, weightf);
	double pressure = spressure(particles, count, point, weightf);
	for(int a = 0; a < SPHAXES; a++) pressureg[a] = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[SPHAXES];
		for(int a = 0; a < SPHAXES; a++)
			displacement[a] = point[a] - particles[p]->position[a];
		double weightg[SPHAXES];
		weightgf(displacement, weightg);
		for(int a = 0; a < SPHAXES; a++)
			pressureg[a] += particles[p]->mass * (
				particles[p]->pressure / particles[p]->density *
				density / particles[p]->density +
				pressure / density
			) * weightg[a];
	}
}

void svelocityl(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double velocityl[SPHAXES],
	double (*weightf)(double point[SPHAXES]),
	void (*weightlf)(double point[SPHAXES], double weightl[SPHAXES])
)
{
	double velocity[SPHAXES];
	svelocity(particles, count, point, velocity, weightf);
	for(int a = 0; a < SPHAXES; a++) velocityl[a] = 0.0;
	for(int p = 0; p < count; p++)
	{
		double displacement[SPHAXES];
		for(int a = 0; a < SPHAXES; a++)
			displacement[a] = point[a] - particles[p]->position[a];
		double weightl[SPHAXES];
		weightlf(displacement, weightl);
		for(int a = 0; a < SPHAXES; a++)
			velocityl[a] += (
				particles[p]->mass *
				(particles[p]->velocity[a] - velocity[a]) /
				particles[p]->density
			) * weightl[a];
	}
}

#endif
