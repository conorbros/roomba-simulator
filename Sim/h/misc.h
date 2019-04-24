#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

bool is_opaque(int x, int y, int left, int top, int width, int height, char pixels[]);

bool pixel_collision(int x0, int y0, int w0, int h0, char pixels0[], int x1, int y1, int w1, int h1, char pixels1[]);

int random_range(int Min, int Max);

bool border_overlap(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);