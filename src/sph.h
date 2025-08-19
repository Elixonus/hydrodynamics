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
	double (*weightf)(double offset[SPHAXES])
);

double spressure(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double offset[SPHAXES])
);

void svelocity(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double offset[SPHAXES]),
	double result[SPHAXES]
);

void spressureg(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double offset[SPHAXES]),
	void (*weightgf)(double offset[SPHAXES], double weightg[SPHAXES]),
	double result[SPHAXES]
);

void svelocityl(
	struct particle **particles,
	int count,
	double point[SPHAXES],
	double (*weightf)(double offset[SPHAXES]),
	void (*weightlf)(double offset[SPHAXES], double weightl[SPHAXES]),
	double result[SPHAXES]
);

#endif
#endif
