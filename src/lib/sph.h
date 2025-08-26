#pragma once

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
);

double spressure(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double radius)
);

void svelocity(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double radius),
	double result[SPHAXES]
);

void spressureg(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double radius),
	void (*weightgf)(double radius, double result[SPHAXES]),
	double result[SPHAXES]
);

void svelocityl(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double radius),
	void (*weightlf)(double radius, double result[SPHAXES]),
	double result[SPHAXES]
);

#endif
