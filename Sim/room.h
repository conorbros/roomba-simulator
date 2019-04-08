#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

int get_dust_count();

void drop_dust(int x, int y);

void drop_dust_input();

int get_charging_station_x_position();

int get_charging_station_y_position();

char* get_charging_station();

void draw_charging_station();

void draw_room();

void init_room();