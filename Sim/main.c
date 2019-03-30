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

void setup () {
    get_screen_size(&width, &height);
    init_robot();
    draw_gui();
    draw_robot();
    time_running = 0.00;
    time_start = 0.00;
}


void loop() {
    clear_screen();
    update_robot(90);
    draw_gui();
    draw_border();
    draw_status_items();
    show_screen();
}

int main() {

    setup_screen();
    setup();
    show_screen();

    start_timer();

    while (1) {
        time_running = get_current_time() - time_start;

        int input = get_char();
        process_input(input);

        loop();
        timer_pause(time_slice);
        draw_status_items();
    }

    return 0;
}
