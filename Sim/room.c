#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include "drawing.h"

static int width;
static int height;

void draw_charging_station(){
    char * charging_station =
    "#########"
    "#########"
    "#########";

    draw_pixels(width / 2 - 4, 7, 9, 3, charging_station, false);
}

void draw_room(){
    draw_charging_station();
}

void init_room(){
    get_screen_size(&width, &height);
}

