#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include "gui.h"
#include "robot.h"
#include "main.h"
#include "helpers.h"

static int width;
static int height;

void write_help_instructions(){
    int x_pos = width / 2 - 38;
    draw_string(x_pos, 10, "b: tell the device to return to base");
    draw_string(x_pos, 11, "d: drop a piece of dust");
    draw_string(x_pos, 12, "i: push the device one unit north");
    draw_string(x_pos, 13, "j: push the device one unit west");
    draw_string(x_pos, 14, "k: push the device one unit south");
    draw_string(x_pos, 15, "l: push the device one unit east");
    draw_string(x_pos, 16, "m: set the delay in milliseconds");
    draw_string(x_pos, 17, "o: set the time-out period");
    draw_string(x_pos, 18, "p: quit the simulation");
    draw_string(x_pos, 19, "r: reset the simulation");
    draw_string(x_pos, 20, "s: drop a piece of slime");
    draw_string(x_pos, 21, "t: drop a piece of trash");
    draw_string(x_pos, 22, "v: move the device to a new location");
    draw_string(x_pos, 23, "w: change the amount (weight) of the rubbish currently on board the device");
    draw_string(x_pos, 24, "y: change the battery level");
    draw_string(x_pos, 26, "Press any key to exit");
}

void display_help_screen(){
    clear_screen();
    write_help_instructions();
    show_screen();

    while(!wait_char()){
        continue;
    }
}

void process_input(char input){
    get_screen_size(&width, &height);

    switch (input)
    {
        //tell the device to stop cleaning and return to base i.e. step repeatedly towards the charging dock.
        case 'b':
            set_robot_return_to_base();
            break;

        //drop a piece of dust (small rubbish) on the floor.
        case 'd':

            break;

        //set the millisecond delay between successive invocations of the loop function.
        case 'm':
            set_delay();
            break;

        //set the time-out period, that is, the total permitted run time, measured in seconds.
        case 'o':
            set_delay();
            break;

        //cause the device to start moving (if it is stationary) or stop moving (if it is mobile).
        case 'p':
            toggle_robot_moving();
            break;

        //quit simulation.
        case 'q':
            quit();
            break;

        //reset simulation.
        case 'r':
            reset();
            break;

        //drop a piece of slime (medium rubbish) on the floor.
        case 's':

            break;

        //drop a piece of trash (large rubbish) on the floor.
        case 't':

            break;

        //move the device to a new location and specify a new direction.
        case 'v':
            set_robot_location_and_direction();
            break;

        //change the amount (weight) of the rubbish currently on board the device.
        case 'w':

            break;

        //change the battery level of the device.
        case 'y':
            set_robot_battery();
            break;
        //push up
        case 'i':
            push_robot_up();
            break;
        //push left
        case 'j':
            push_robot_left();
            break;
        //push right
        case 'k':
            push_robot_down();
            break;
        //push down
        case 'l':
            push_robot_right();
            break;
        case '?':
            display_help_screen();
            break;

        default:
            break;
    }
}

