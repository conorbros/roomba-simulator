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

double get_robot_direction(){
    return robot_direction;
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

int RandRange(int Min, int Max){
    int diff = Max-Min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + Min);
}

double swivel_robot(){
    int left = (rand() > RAND_MAX/2) ? 0 : 1;
    double new_facing = robot_direction;

    if(left){
        new_facing -= 30 + RandRange(0, 30);
    }else{
        new_facing += 30 + RandRange(0, 30);
    }

    if (new_facing > 364){
        new_facing = (int)new_facing % 365;
    }else if (new_facing < 0){
        new_facing = (int)new_facing % -365;
    }

    return new_facing;
}

bool wall_collision(){
    return (0 >= robot_x_pos -1 ) || (0 > robot_y_pos - 8) || (get_screen_width() < robot_x_pos + 10) || (get_screen_height() - 4 < robot_y_pos);
}


void move_robot(){

    if(wall_collision()){

        robot_direction = swivel_robot();

    }

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

