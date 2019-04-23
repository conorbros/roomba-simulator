#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

int get_dust_count();

char * get_dust();

int * get_dust_x_positions();

int * get_dust_y_positions();

void drop_dust(int x, int y);

void drop_dust_input();

void pickup_dust(int index);

int get_charging_station_x_position();

int get_charging_station_y_position();

char* get_charging_station();

void draw_charging_station();

void draw_room();

void init_room();