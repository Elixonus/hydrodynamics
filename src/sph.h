#ifndef SPHHEADER
#define SPHHEADER
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
);

double spressure(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double point[SPHAXES])
);

double *svelocity(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double velocity[SPHAXES],
	double (*weightf)(double point[SPHAXES])
);

double *spressureg(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double pressureg[SPHAXES],
	double (*weightf)(double point[SPHAXES]),
	void (*weightgf)(double point[SPHAXES], double weightg[SPHAXES])
);

double *svelocityl(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double velocityl[SPHAXES],
	double (*weightf)(double point[SPHAXES]),
	void (*weightlf)(double point[SPHAXES], double weightl[SPHAXES])
);

#endif
#endif
