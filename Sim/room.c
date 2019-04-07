#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include "drawing.h"

static int width;
static int height;

static int charging_station_x_position;
static int charging_station_y_position;

static int dust_x_positions[1000];
static int dust_y_positions[1000];

static char * charging_station =
    "#########"
    "#########"
    "#########";

static char * dust =
    ".";

static char * trash =
    "     &     "
    "    &&&    "
    "   &&&&&   "
    "  &&&&&&&  "
    " &&&&&&&&& "
    "&&&&&&&&&&&";

static char * slime =
    " ~~~ "
    "~~~~~"
    "~~~~~"
    "~~~~~"
    " ~~~ ";

void drop_dust(int x, int y){
    dust_x_positions
}

int get_charging_station_x_position(){
    return charging_station_x_position;
}

int get_charging_station_y_position(){
    return charging_station_y_position;
}

char* get_charging_station(){
    return charging_station;
}

void draw_charging_station(){
    draw_pixels(charging_station_x_position, charging_station_y_position, 9, 3, charging_station, false);
}

void draw_room(){
    draw_charging_station();
}

void init_room(){
    get_screen_size(&width, &height);
    charging_station_x_position = width/2 - 5;
    charging_station_y_position = 7;


}

