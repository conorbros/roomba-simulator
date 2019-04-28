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
int get_slime_count();
char * get_slime();
int get_slime_side();
int * get_slime_y_positions();
int * get_slime_x_positions();
void drop_slime_input();
void pickup_slime(int index);
int get_trash_count();
int get_trash_width();
int get_trash_height();
char * get_trash();
int * get_trash_x_positions();
int * get_trash_y_positions();
void drop_trash_input();
void pickup_trash(int index);
int get_charging_station_x_position();
int get_charging_station_y_position();
char* get_charging_station();
void draw_charging_station();
void draw_room();
void init_rubbish();
void init_room();