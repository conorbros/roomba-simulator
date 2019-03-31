//Conor Brosnan - n10009671 - CAB202 Assignment 1
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <../ZDK/cab202_graphics.h>
#include <../ZDK/cab202_timers.h>

// Insert other functions here, or include header files
#include <gui.h>

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
