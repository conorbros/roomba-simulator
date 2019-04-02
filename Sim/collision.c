#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

bool is_opaque(int x, int y, int left, int top,
    int width, int height, char pixels[])
{
    return x >= left
        && x < left + width
        && y >= top
        && y < top + height
        && pixels[(x - left) + (y - top) * width] != ' ';
}

bool pixel_collision(int x0, int y0, int w0, int h0, char pixels0[],
    int x1, int y1, int w1, int h1, char pixels1[])
{
    for(int j = y0; j < h0 + y0; j++){
        for(int i = x0; i < w0 + x1; i++){
            if (is_opaque(i, j, x0, y0, w0, h0, pixels0)
                && is_opaque(i, j, x1, y1, w1, h1, pixels1)){
                    return true;
                }
        }
    }
    return false;
}
