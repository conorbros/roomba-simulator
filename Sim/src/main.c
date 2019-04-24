//Conor Brosnan - n10009671 - CAB202 Assignment 1
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include <robot.h>
#include <gui.h>
#include <input_control.h>
#include <room.h>
#include <helpers.h>

static bool simulation_quit;
static int delay;

void set_delay(){
    int input = get_int("Set the new loop delay: ");
    delay = input;
}

void loop(){
    char input = get_char();
    process_input(input);
    clear_screen();
    update_timer();
    update_battery();
    draw_gui();
    draw_room();
    update_robot();
    show_screen();
    set_time_at_last_loop();
}

void reset(){
    start_timer();
    init_robot();
    init_room();
    draw_robot();
    draw_room();
}

void quit(){
    simulation_quit = true;
}


void room_setup(){
    int dust = get_int("How much dust: ");

    if (dust < 0) dust = 0;
    if (dust > 1000) dust = 1000;

    int slime = get_int("How much slime: ");

    if (slime < 0) slime = 0;
    if (slime > 10) slime = 10;

    init_room(dust, slime);
}

int main(){
    delay = 50;

    setup_screen();
    show_screen();
    room_setup();
    start_timer();
    init_robot();
    init_rubbish();
    draw_robot();
    draw_room();

    simulation_quit = false;

    while (!simulation_quit) {

        loop();
        timer_pause(delay);
    }

    simulation_quit_message();
    return 0;
}
