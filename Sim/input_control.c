#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

void process_input(char input){
    int width, height;
    get_screen_size(&width, &height);

    //echo char to command window
    draw_char(width / 2, height - 2, input);

    switch (input)
    {
        //tell the device to stop cleaning and return to base i.e. step repeatedly towards the charging dock.
        case 'b':
            /* code */
            break;

        //drop a piece of dust (small rubbish) on the floor.
        case 'd':

            break;

        //set the millisecond delay between successive invocations of the loop function.
        case 'm':

            break;

        //set the time-out period, that is, the total permitted run time, measured in seconds.
        case 'o':

            break;

        //cause the device to start moving (if it is stationary) or stop moving (if it is mobile).
        case 'p':

            break;

        //quit simulation.
        case 'q':

            break;

        //reset simulation.
        case 'r':

            break;

        //drop a piece of slime (medium rubbish) on the floor.
        case 's':

            break;

        //drop a piece of trash (large rubbish) on the floor.
        case 't':

            break;

        //move the device to a new location and specify a new direction.
        case 'v':

            break;

        //change the amount (weight) of the rubbish currently on board the device.
        case 'w':

            break;

        //change the battery level of the device.
        case 'y':

            break;

        default:
            break;
    }
}

