#include "storage.h"

void integrate_euler_explicit(struct particle *particle, double dt)
{
	for(int j = 0; j < 3; j++)
	{
		particle->basic.v[j] += particle->a[j] * dt;
		particle->basic.r[j] += partcle->basic.v[j] * dt;
	}
}
