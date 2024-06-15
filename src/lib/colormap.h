#ifndef COLORMAP_H
#define COLORMAP_H

extern float colors[256][3];

void load_colormap(void);
int index_colormap(double value);

#endif