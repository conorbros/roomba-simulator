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

static int time_out = INT_MAX;
static bool simulation_quit = false;;
static int delay = 50;

void set_delay(){
    int input = get_int("Set the new loop delay: ");
    delay = input;
}

void room_setup(){
    int dust = get_int("How much dust: ");
    if (dust < 0) dust = 0;
    if (dust > 1000) dust = 1000;

    int slime = get_int("How much slime: ");
    if (slime < 0) slime = 0;
    //if (slime > 10) slime = 10;

    int trash = get_int("How much trash: ");
    if (trash < 0) trash = 0;
    //if (trash > 5) trash = 5;

    init_room(dust, slime, trash);
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
    room_setup();
    start_timer();
    init_robot();
    init_rubbish();
    draw_robot();
    draw_room();
}

void set_timeout(){
    time_out = get_int("Set the timeout duration for the simulation: ");
}

bool timed_out(){
    return get_current_time() - get_time_start() >= time_out;
}

void quit(){
    simulation_quit = true;
}

int main(){

    setup_screen();
    show_screen();
    room_setup();
    start_timer();
    init_robot();
    init_rubbish();
    draw_robot();
    draw_room();

    while (!simulation_quit) {

        if(timed_out()) return 0;

        loop();
        timer_pause(delay);
    }

    simulation_quit_message();
    return 0;
}
