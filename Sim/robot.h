#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

char* get_robot();

int get_robot_x_pos();

int get_robot_y_pos();

int get_robot_battery();

void set_robot_battery();

int get_robot_weight();

void set_robot_weight();

bool is_robot_docked();

double get_robot_direction();

void toggle_robot_moving();

void set_robot_x_pos();

void set_robot_y_pos();

void set_robot_direction();

void set_robot_location_and_direction();

void set_robot_return_to_base();

void update_battery();

void draw_robot();

double swivel_robot();

bool is_charging_station_collision();

bool is_left_wall_collision();

bool is_top_wall_collision();

bool is_bottom_wall_collision();

bool is_right_wall_collision();

void is_wall_collision();

void update_robot();

void push_robot_up();

void push_robot_left();

void push_robot_right();

void push_robot_down();

void update_robot();

void init_robot();