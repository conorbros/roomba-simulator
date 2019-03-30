//Conor Brosnan - n10009671 - CAB202 Assignment 1
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

// Insert other functions here, or include header files

void reset(){
    init_robot();
    time_running = 0;
    time_start = get_current_time();
}


void loop() {
    clear_screen();
    update_timer();
    draw_gui();
    show_screen();
}

int main() {

    show_screen();

    start_timer();

    while (1) {
        loop();
        timer_pause(time_slice);

    }

    return 0;
}
