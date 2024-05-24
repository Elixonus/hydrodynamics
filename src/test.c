#include <stdio.h>
#include <stdlib.h>
#include "lib/sph.h"
#include "lib/ker.h"


int main(void)
{
	double r1[3] = {2.2, 2.2, 0.0};
	double r2[3] = {-1.5, 0.0, 0.0};
	double r3[3] = {0.0, -2.0, 0.0};
	struct s particles[3];
	particles[0].m = 1.0;
	particles[1].m = 1.0;
	particles[2].m = 1.0;
	for(int c = 0; c < 3; c++)
	{
		particles[0].r[c] = r1[c];
		particles[1].r[c] = r2[c];
		particles[2].r[c] = r3[c];
	}
	double r[3] = {0.0, 0.0, 0.0};
	double vr[3];
	v(r, vr);
	printf("v(r): <%f, %f, %f>\n", vr[0], vr[1], vr[2]);

}
