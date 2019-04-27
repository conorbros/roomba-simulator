#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

static bool rand_seeded = false;

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
            if (is_opaque(i, j, x0, y0, w0, h0, pixels0) && is_opaque(i, j, x1, y1, w1, h1, pixels1)){
                    return true;
                }
        }
    }
    return false;
}

int random_range(int min, int max){

    if(!rand_seeded) srand(time(NULL));
    rand_seeded = true;
    return (rand() % (max + 1 - min)) + min;
}

bool border_overlap(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){

    return x1 < x2 - w2 && x1 - w1 > x2 && y1 > y2 - h2 && y1 - h1 < y1;

}
