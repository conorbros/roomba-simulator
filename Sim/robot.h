#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

int get_robot_battery();

double get_robot_direction();

void toggle_robot_moving();

void decrement_battery();

void draw_robot();

int RandRange(int Min, int Max);

double swivel_robot();

void wall_collision();

void move_robot(double angle);

void init_robot();