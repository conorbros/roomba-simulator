#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include "gui.h"

static int robot_battery;

static double robot_x_pos;
static double robot_y_pos;
static double robot_direction;

static bool robot_moving;

static const double velocity = 0.2;

#define M_PI 3.14159265358979323846

int get_robot_battery(){
    return robot_battery;
}

void toggle_robot_moving(){
    robot_moving = !robot_moving;
}

void decrement_battery(){
    if (floor(get_current_time()) - get_time_start() > get_time_at_last_loop()){
        robot_battery--;
    }
}

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

    draw_pixels(robot_x_pos - 4, robot_y_pos - 4, 9, 9, robot, true);
}


void wall_collision(){
    if (0 > robot_x_pos){
        robot_direction = 0;
    }else if (0 > robot_y_pos - 7){
        robot_direction = 90;
    }else if (get_screen_width() < robot_x_pos + 7){
        robot_direction = 180;
    }else if (get_screen_height() < robot_y_pos + 9){
        robot_direction = 270;
    }
}


void move_robot(){
    wall_collision();
    if(robot_moving){
        robot_x_pos += velocity * cos(robot_direction * M_PI / 180);
        robot_y_pos += velocity * sin(robot_direction * M_PI / 180);
    }
    draw_robot();
}

void init_robot(){
    int width, height;
    get_screen_size(&width, &height);
    robot_battery = 100;
    robot_x_pos = width / 2, robot_y_pos = height / 2;
    robot_moving = false;
    robot_direction = 90;
}

