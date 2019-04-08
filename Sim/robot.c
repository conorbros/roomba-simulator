#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include "gui.h"
#include "room.h"
#include "misc.h"
#include "helpers.h"

static int width;
static int height;

static int robot_battery;
static int robot_weight;

static int robot_x_pos;
static int robot_y_pos;
static int robot_direction;
int robot_side = 9;

static bool robot_moving;
static bool manual_control;
static bool return_to_base;
static bool docked;
static int seconds_of_charging;
static bool robot_turned;

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

char* get_robot(){
    return robot;
}

int get_robot_x_pos(){
    return (int)robot_x_pos;
}

int get_robot_y_pos(){
    return (int) robot_y_pos;
}

int get_robot_battery(){
    return robot_battery;
}

void set_robot_battery(){
    int input = get_int("Set the robot's battery: ");

    input++;

    if(input > 100) input = 100;
    if(input < 0) input = 0;

    robot_battery = input;
}

int get_robot_weight(){
    return robot_weight;
}

void set_robot_weight(){
    int input = get_int("Set the robot's current weight: ");
    if (input < 0){
        input = 0;
    }

    robot_weight = input;
}

bool is_robot_docked(){
    return docked;
}

double get_robot_direction(){
    return robot_direction;
}

void toggle_robot_moving(){
    robot_moving = !robot_moving;
}

// TODO: CHECK WONT COLLIDE WITH CHARGING STATION
void set_robot_x_pos(){
    int x_pos = get_int("Set robot X position: ");

    if(x_pos <= 0) {
        x_pos = 1;
    }else if(x_pos + robot_side >= width) {
        x_pos = width - (robot_side + 1);
    }

    robot_x_pos = x_pos;
}

// TODO: CHECK WONT COLLIDE WITH CHARGING STATION
void set_robot_y_pos(){
    int y_pos = get_int("Set robot Y position: ");
    if(y_pos <= 7) {
        y_pos = 7;
    }else if(y_pos + robot_side >= height - 3) {
        y_pos = height - (robot_side + 4);
    }

    robot_y_pos = y_pos;
}

void set_robot_direction(){
    int direction = get_int("Set robot direction: ");
    if(direction > 360 || direction < 0) direction = 0;
    robot_direction = direction;
}

void set_robot_location_and_direction(){
    set_robot_x_pos();
    set_robot_y_pos();
    set_robot_direction();
    manual_control = true;
}

void set_robot_return_to_base(){
    return_to_base = true;
    double t1 = get_charging_station_x_position() - robot_x_pos;
    double t2 = get_charging_station_y_position() + 4 - robot_y_pos;

    double d = sqrt(t1 * t1 + t2 * t2);
    base_dx = t1 * 0.35 / d;
    base_dy = t2 * 0.35 /d;
}

void increment_battery(){
    robot_battery++;
    if (robot_battery > 100){
        robot_battery = 100;
    }
}

void decrement_battery(){
    robot_battery--;
    if (robot_battery < 0){
        robot_battery = 0;
    }
}

void docking_control(){
    if(floor(get_current_time())  >= get_time_at_last_loop() + 30.00 ) increment_battery();

    draw_string((width / 2) - 3, height - 2, "DOCKED");

    if (robot_battery == 100){
        docked = false;
        robot_moving = true;
        robot_battery = 100;
        seconds_of_charging = 0;
        return_to_base = false;
    }
}

void update_battery(){
    if(robot_moving && !docked && (floor(get_current_time()) - get_time_start() > get_time_at_last_loop())){
        decrement_battery();
    }

    if(docked) docking_control();

    if(robot_battery <= 25) set_robot_return_to_base();

    if(robot_battery == 0) simulation_over_message();
}

void draw_robot(){
    draw_pixels(robot_x_pos, robot_y_pos, robot_side, robot_side, robot, true);
}

double swivel_robot(){
    int new_facing = random_range(0, 30) + 30;
    int returnVal = ((int)robot_direction + new_facing) % 360;
    return returnVal;
}

bool left_side_charging_station(){
    return (robot_x_pos < get_charging_station_x_position() && robot_x_pos + 10 > get_charging_station_x_position()
        && robot_y_pos < get_charging_station_y_position() + 2);
}

bool right_side_charging_station(){
    return (robot_x_pos - 1 <= get_charging_station_x_position() + 9
        && robot_x_pos + robot_side > get_charging_station_x_position() + 9
        && robot_y_pos <= get_charging_station_y_position() + 2);
}

bool bottom_side_charging_station(){

    if (robot_x_pos < get_charging_station_x_position()
        && robot_x_pos + robot_side > get_charging_station_x_position()
        && robot_y_pos < get_charging_station_y_position() + 4) return true;

    if (robot_x_pos < get_charging_station_x_position() + robot_side
        && robot_x_pos + robot_side > get_charging_station_x_position() + 9
        && robot_y_pos < get_charging_station_y_position() + 4) return true;

    return false;
}

bool is_charging_station_collision(){
    return pixel_collision(
        robot_x_pos - 1, robot_y_pos - 1, robot_side, robot_side, robot,
        get_charging_station_x_position(), get_charging_station_y_position(), 9, 3, get_charging_station()
    );
}

bool is_left_wall_collision(){
    return (2 >= robot_x_pos - 1);
}

bool is_top_wall_collision(){
    return (7 > robot_y_pos - 1);
}

bool is_bottom_wall_collision(){
    if (manual_control) return (get_screen_height() - 4 < robot_y_pos + 10);
    return (get_screen_height() - 4 < robot_y_pos + 9);
}

bool is_right_wall_collision(){
    return (get_screen_width() < robot_x_pos + 11);
}

bool is_wall_collision(){
    return (is_left_wall_collision() || is_top_wall_collision() ||
       is_right_wall_collision() || is_bottom_wall_collision());
}

void move_robot(){

    if(robot_moving && !manual_control){

        if(return_to_base){
            if(!is_charging_station_collision()){
                robot_x_pos += base_dx;
                robot_y_pos += base_dy;
            }else{
                robot_moving = false;
                docked = true;
            }

        }else if((is_wall_collision() || is_charging_station_collision())
            && !robot_turned){
            robot_direction = swivel_robot();
            robot_turned = true;
            draw_robot();
            return;
        }else{
            robot_turned = false;
            robot_x_pos += velocity * cos(robot_direction * M_PI / 180);
            robot_y_pos += velocity * sin(robot_direction * M_PI / 180);
        }
    }

    draw_robot();
    manual_control = false;
}

void push_robot_up(){
    manual_control = true;
    if(!is_top_wall_collision() && !bottom_side_charging_station()){
        robot_y_pos--;
    }
}

void push_robot_left(){
    manual_control = true;
    if(!is_left_wall_collision() && !right_side_charging_station()){
        robot_x_pos--;
    }
}

void push_robot_right(){
    manual_control = true;
    if(!is_right_wall_collision() && !left_side_charging_station()){
        robot_x_pos++;
    }
}

void push_robot_down(){
    manual_control = true;
    if(!is_bottom_wall_collision()){
        robot_y_pos++;
    }
}

void init_robot(){
    get_screen_size(&width, &height);

    robot_battery = 100;
    robot_weight = 0;
    robot_x_pos = (width / 2) - 4;
    robot_y_pos = (height / 2) - 4;

    robot_moving = false;
    robot_direction = 90;

    seconds_of_charging = 0;
    manual_control = false;
    return_to_base = false;
}
