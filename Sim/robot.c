#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

static int robot_weight;
static int robot_battery;

static double robot_x_pos;
static double robot_y_pos;
static double robot_direction_angle;

static bool robot_moving;
static bool return_to_base;

static const double velocity = 0.2;

#define M_PI 3.14159265358979323846;


int get_robot_weight(){
    return robot_weight;
}

void set_robot_weight(int weight){
    robot_weight = weight;
}

int get_robot_battery(){
    return robot_battery;
}

void set_robot_battery(int battery){
    robot_battery = battery;
}

void decrement_battery(){
    robot_battery--;
}

bool set_return_to_base(bool value){
    return_to_base = value;
}

bool get_return_to_base(){
    return return_to_base;
}

bool get_robot_moving(){
    return robot_moving;
}

void toggle_robot_moving(){
    robot_moving = !robot_moving;
}

/**
 * draws the robot at its current position
 */
void draw_robot(){
    char * robot =
    "  @@@@@  "
    " @     @ "
    "@       @"
    "@       @"
    "@       @"
    "@       @"
    "@       @"
    " @     @ "
    "  @@@@@  ";

    draw_pixels(robot_x_pos - 4, robot_y_pos - 4, 9, 9, robot, false);
}

void move_robot(double angle){
    robot_x_pos += velocity * cos(angle * M_PI / 180);
    robot_y_pos += velocity * sin(angle * M_PI / 180);
    draw_robot();
}

void init_robot(){
    robot_battery = 100;
    robot_weight = 0;
    robot_x_pos = width / 2, robot_y_pos = height / 2;
    return_to_base = false;
    robot_moving = false;
}

