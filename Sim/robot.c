#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include "gui.h"
#include "room.h"
#include "collision.h"

static int robot_battery;
static int seconds_of_charging;

static double robot_x_pos;
static double robot_y_pos;
static double robot_direction;

static bool robot_moving;
static bool manual_control;
static bool return_to_base;
static bool docked;

static double base_dx;
static double base_dy;

static const double velocity = 0.2;

#define M_PI 3.14159265358979323846


static char * robot =
    "  @@@@@  "
    " @=====@ "
    "@=^===^=@"
    "@=O===O=@"
    "@===>===@"
    "@=======@"
    "@=\\___/=@"
    " @=====@ "
    "  @@@@@  ";

int get_robot_battery(){
    return robot_battery;
}

double get_robot_direction(){
    return robot_direction;
}

void toggle_robot_moving(){
    robot_moving = !robot_moving;
}

void set_robot_return_to_base(){
    return_to_base = true;
    double t1 = get_charging_station_x_position() - robot_x_pos;
    double t2 = get_charging_station_y_position() + 4 - robot_y_pos;

    double d = sqrt(t1 * t1 + t2 * t2);
    base_dx = t1 * 0.35 / d;
    base_dy = t2 * 0.35 /d;
}

void update_battery(){
    if(!docked && (floor(get_current_time()) - get_time_start() > get_time_at_last_loop())){
        robot_battery--;
    }

    if(docked){
        if (seconds_of_charging > 3){
            docked = false;
            robot_moving = true;
            robot_battery = 100;
            seconds_of_charging = 0;
        }

        if(floor(get_current_time()) - get_time_start() > get_time_at_last_loop()){
            seconds_of_charging ++;
        }
    }

    if(robot_battery <= 25){ return_to_base = true;}
    if(robot_battery == 0){ robot_moving = false;}
}

void draw_robot(){
    draw_pixels(robot_x_pos, robot_y_pos, 9, 9, robot, true);
}

int RandRange(int Min, int Max){
    int diff = Max-Min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + Min);
}

double swivel_robot(){
    int new_facing = RandRange(0, 30) + 30;
    int returnVal = ((int)robot_direction + new_facing) % 360;
    return returnVal;
}

bool is_charging_station_collision(){
    return pixel_collision(
        robot_x_pos - 1, robot_y_pos - 1, 11, 11, robot,
        get_charging_station_x_position(), get_charging_station_y_position(), 9, 3, get_charging_station()
    );
}

bool is_left_wall_collision(){
    return (0 >= robot_x_pos - 1);
}

bool is_top_wall_collision(){
    return (7 > robot_y_pos - 1);
}

bool is_bottom_wall_collision(){
    return (get_screen_height() - 4 < robot_y_pos + 10);
}

bool is_right_wall_collision(){
    return (get_screen_width() < robot_x_pos + 11);
}

bool is_wall_collision(){
    return (is_left_wall_collision() || is_top_wall_collision() ||
        is_right_wall_collision() || is_bottom_wall_collision());
}

void move_robot(){
    if(robot_moving){

        if(is_wall_collision() || (is_charging_station_collision() && !return_to_base) || docked){
            robot_direction = swivel_robot();
        }


        if(return_to_base){
            if(!is_charging_station_collision()){
                robot_x_pos += base_dx;
                robot_y_pos += base_dy;
            }else{
                robot_moving = false;
                docked = true;
            }

        }else{
            robot_x_pos += velocity * cos(robot_direction * M_PI / 180);
            robot_y_pos += velocity * sin(robot_direction * M_PI / 180);
        }

    }
    draw_robot();
    manual_control = false;
}

void push_robot_up(){
    if(!is_top_wall_collision() && !is_charging_station_collision()){
        robot_y_pos--;
    }
}

void push_robot_left(){
    if(!is_left_wall_collision() && !is_charging_station_collision()){
        robot_x_pos--;
    }
}

void push_robot_right(){
    if(!is_right_wall_collision() && !is_charging_station_collision()){
        robot_x_pos++;
    }
}

void push_robot_down(){
    if(!is_bottom_wall_collision() && !is_charging_station_collision()){
        robot_y_pos++;
    }
}

void init_robot(){
    int width;
    int height;
    get_screen_size(&width, &height);
    robot_battery = 100;
    robot_x_pos = width / 2;
    robot_y_pos = height / 2;
    robot_moving = false;
    robot_direction = 90;
    seconds_of_charging = 0;
    manual_control = false;
}
