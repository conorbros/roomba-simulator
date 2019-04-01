//Conor Brosnan - n10009671 - CAB202 Assignment 1
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

// Insert other functions here, or include header files

#include "robot.h"
#include "gui.h"
#include "input_control.h"

void loop(){
    clear_screen();
    update_timer();
    decrement_battery();
    draw_gui();
    move_robot(90.00);
    show_screen();
    set_time_at_last_loop();
}

int main(){

    setup_screen();
    show_screen();
    start_timer();
    init_robot();
    draw_robot();
    while (1) {
        char input = get_char();
        process_input(input);
        loop();
        timer_pause(40);
    }

    return 0;
}
