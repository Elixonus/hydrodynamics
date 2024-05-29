#include "storage.h"

void allocate_particles(void);
void reallocate_particles(void);
void deallocate_particles(void);
void allocate_cparticles(struct cell *cell);
void reallocate_cparticles(struct cell *cell);
void deallocate_cparticles(struct cell *cell);
void allocate_cells(void);
void deallocate_cells(void);
