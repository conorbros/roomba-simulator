#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include <gui.h>
#include <room.h>
#include <helpers.h>

static int width;
static int height;
static int robot_battery;
static int robot_weight;

static double robot_x_pos;
static double robot_y_pos;
static int robot_direction;
int robot_side = 9;

static bool robot_moving;
static bool manual_control;
static bool return_to_base;
static bool docked;

static int seconds_of_charging;
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
    return (int)robot_y_pos;
}

int get_robot_battery(){
    return robot_battery;
}

 /**
 *  Sets the robot's battery manually, ensures that it stays within the lower and upper limits
 */
void set_robot_battery(){
    int input = get_int("Set the robot's battery: ");
    if(input > 100) input = 100;
    if(input < 0) input = 0;
    robot_battery = input;
}

int get_robot_weight(){
    return robot_weight;
}

 /**
 *  Sets the robot's weight manually, ensures that it stays within the lower and upper limits
 */
void set_robot_weight(){
    int input = get_int("Set the robot's current weight: ");
    if (input < 0) input = 0;
    if (input > 65) input = 65;
    robot_weight = input;
}

 /**
 *  Adds rubbish weight to the robot, if weight above or equal to 45, set robot to RTB
 */
void robot_pickup_rubbish(int weight){
    robot_weight += weight;
    if(robot_weight > 45) return_to_base = true;
}

double get_robot_direction(){
    return robot_direction;
}

void toggle_robot_moving(){
    robot_moving = !robot_moving;
}

 /**
 *  Sets the robot's x position manually, will ensure it stays within the border
 */
int set_robot_x_pos(){
    int x_pos = get_int("Set robot X position: ");

    if(x_pos <= 0) {
        x_pos = 1;
    }else if(x_pos + robot_side >= width) {
        x_pos = width - (robot_side + 1);
    }

    return x_pos;
}

 /**
 *  Sets the robot's y position manually, will ensure it stays within the border
 */
int set_robot_y_pos(){
    int y_pos = get_int("Set robot Y position: ");

    if(y_pos <= 7) {
        y_pos = 7;
    }else if(y_pos + robot_side >= height - 3) {
        y_pos = height - (robot_side + 4);
    }

    return y_pos;
}

 /**
 *  Sets the robot direction, ensures it does not go outside the allowed values
 */
void set_robot_direction(){
    int direction = get_int("Set robot direction: ");
    if(direction > 360 || direction < 0) direction = 0;
    robot_direction = direction;
}

 /**
 *  Sets the robot's location and direction manually,
 *  Will not relocate if it will collide the charging station
 */
void set_robot_location_and_direction(){
    int x = set_robot_x_pos();
    int y = set_robot_y_pos();

    if (pixel_collision(x, y, robot_side, robot_side, robot,
        get_charging_station_x_position(), get_charging_station_y_position(), 9, 3, get_charging_station())) return;

    robot_x_pos = x;
    robot_y_pos = y;
    set_robot_direction();
    manual_control = true;
}

 /**
 *  Sets the robot base_dx and base_dy variables to use as a trajectory
 *  to the charging station from its current position
 */
void set_base_trajectory(){
    double t1 = (double)get_charging_station_x_position() - robot_x_pos;
    double t2 = (double)get_charging_station_y_position() - robot_y_pos;

    double d = sqrt(t1 * t1 + t2 * t2);
    base_dx = t1 * velocity / d;
    base_dy = t2 * velocity /d;
}

void set_robot_return_to_base(){
    return_to_base = true;
    set_base_trajectory();
}

void increment_battery(){
    robot_battery++;
    if (robot_battery > 100) robot_battery = 100;
}

void decrement_battery(){
    robot_battery--;
    if (robot_battery < 0) robot_battery = 0;
}

 /**
 *  Controls the docking of the robot, recharges the battery according to the limit set
 *  If the robot is fully recharged, the robot leaves the charging station with a full battery and empty weight
 */
void docking_control(){
    if(floor(get_current_time())  >= get_time_at_last_loop() + 30.00 ) increment_battery();

    draw_string((width / 2) - 3, height - 2, "DOCKED");

    if (robot_battery == 100){
        docked = false;
        robot_moving = true;
        robot_battery = 100;
        seconds_of_charging = 0;
        return_to_base = false;
        robot_weight = 0;
    }
}

 /**
 *  Updates the robot battery according to its variables, ends the simulation if the robot is out of battery
 *  Sets the robot to return to base if the battery is equal to or below 25
 *  Controls docking if the robot is docked
 */
void update_battery(){
    if(robot_moving && !docked && (floor(get_current_time()) - get_time_start() > get_time_at_last_loop())) decrement_battery();
    if(docked) docking_control();
    if(robot_battery <= 25) set_robot_return_to_base();
    if(robot_battery == 0) simulation_over_message();
}

 /**
 *  Draws the robot at its current x and y position
 */
void draw_robot(){
    draw_pixels(robot_x_pos, robot_y_pos, robot_side, robot_side, robot, true);
}

 /**
 *  Turns the robot in a new direction beteen +30 and +60 degrees
 */
void swivel_robot(){
    int new_facing = (rand() % (30 + 1 - 0)) + 0;
    robot_direction = ((int)robot_direction + new_facing) % 360;
}

/**
 *
 *
 *  Parameters:
 *      x: the possible x position of the robot to test
 *      y: the possible y position of the robot to test
 *
 *  Returns:
 *      true if collision, false if not
 */
bool charging_station_collision(double x, double y){
    return pixel_collision(
        (int)x, (int)y, robot_side, robot_side, robot,
        get_charging_station_x_position(), get_charging_station_y_position(), 9, 3, get_charging_station()
    );
}

/**
 *  Determines if the robot has collided with the walls or the charging station
 *
 *  Parameters:
 *      x: the possible x position of the robot to test
 *      y: the possible y position of the robot to test
 *
 *  Returns:
 *      true if collision, false if not
 */
bool object_collision(double x, double y){
    return charging_station_collision(x, y)
        || (int)x == 0 || (int)x + robot_side == width
        || (int)y == 6 || (int)y + robot_side == height - 2;
}

/**
 *  Moves the robot in the appropriate direction based on its current status and variables
 */
void move_robot(){
    //if the robot has been manual controlled and is in RTB mode, the base trajectory will need to be reset
    if(manual_control && return_to_base) set_base_trajectory();

    //if the robot is not moving, docked or has been manually controlled last time slice, it should not be moved automatically
    if(!robot_moving || docked || manual_control){
        manual_control = false;
        draw_robot();
        return;
    }

    double new_x, new_y;

    //Handle RTB mode
    if(return_to_base){
        set_base_trajectory();
        new_x = robot_x_pos + base_dx;
        new_y = robot_y_pos + base_dy;

            //if in RTB and collided with charging station, the robot is docked
            if(charging_station_collision(new_x, new_y)){
                docked = true;
                robot_moving = false;
                draw_robot();
                return;
            }
    }else {
        new_x = robot_x_pos + velocity * cos(robot_direction * M_PI / 180);
        new_y = robot_y_pos + velocity * sin(robot_direction * M_PI / 180);
    }

    //if collision: swivel, otherwise move in the current direction
    if(object_collision(new_x, new_y)){
        swivel_robot();
    }else{
        robot_x_pos = new_x;
        robot_y_pos = new_y;
    }
    draw_robot();
    manual_control = false;
}

/**
 *  Pushes the robot up one coorindate,
 *  provided it will not be pushed through a wall or into the charging station
 */
void push_robot_up(){
    if(object_collision(robot_x_pos, robot_y_pos - 1)) return;
    robot_y_pos--;
    manual_control = true;
}

/**
 *  Pushes the robot down one coorindate,
 *  provided it will not be pushed through a wall or into the charging station
 */
void push_robot_down(){
    if(object_collision(robot_x_pos, robot_y_pos + 1)) return;
    robot_y_pos++;
    manual_control = true;
}

/**
 *  Pushes the robot left one coorindate,
 *  provided it will not be pushed through a wall or into the charging station
 */
void push_robot_left(){
    if(object_collision(robot_x_pos - 1, robot_y_pos)) return;
    robot_x_pos--;
    manual_control = true;
}

 /**
 *  Pushes the robot right one coorindate,
 *  provided it will not be pushed through a wall or into the charging station
 */
void push_robot_right(){
    if(object_collision(robot_x_pos + 1, robot_y_pos)) return;
    robot_x_pos++;
    manual_control = true;
}

/**
 * Determines if the robot has collided with dust and picks it up if so
 */
void dust_collision(){
    int * dust_x = get_dust_x_positions();
    int * dust_y = get_dust_y_positions();

    for(int i = 0; i < get_dust_count(); i++){
        if(pixel_collision(
            robot_x_pos, robot_y_pos, robot_side, robot_side, robot,
            dust_x[i], dust_y[i], 1, 1, get_dust())) pickup_dust(i);
    }
}

/**
 * Determines if the robot has collided with slime and picks it up if so
 */
void slime_collision(){
    int * slime_x = get_slime_x_positions();
    int * slime_y = get_slime_y_positions();

    for(int i = 0; i < get_slime_count(); i++){
        if(pixel_collision(
            robot_x_pos, robot_y_pos, robot_side, robot_side, robot,
            slime_x[i], slime_y[i], get_slime_side(), get_slime_side(), get_slime())) {
                pickup_slime(i);
            };
    }
}

/**
 * Determines if the robot has collided with trash and picks it up if so
 */
void trash_collision(){
    int * trash_x = get_trash_x_positions();
    int * trash_y = get_trash_y_positions();

    for(int i = 0; i < get_trash_count(); i++){
        if(pixel_collision(
            robot_x_pos, robot_y_pos, robot_side, robot_side, robot,
            trash_x[i], trash_y[i], get_trash_width(), get_trash_height(), get_trash())) {
                pickup_trash(i);
            };
    }
}

/**
* Collects rubbish if the robot is not in return to base mode
* Sets the robot to return to base mode if the weight is greater than 45
*/
void rubbish_collision(){

    if(!return_to_base){
        dust_collision();
        slime_collision();
        trash_collision();
    }

    if(robot_weight >= 45) set_robot_return_to_base();
}

/**
 * Moves the robot and detects and handles collision with rubbish
 */
void update_robot(){
    move_robot();
    rubbish_collision();
}

/**
 *
 * Initiazlies the robot to its starting variables, supplies the program with
 * the terminal's width and height
 *
 */
void init_robot(){
    get_screen_size(&width, &height);
    srand(time(0));
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