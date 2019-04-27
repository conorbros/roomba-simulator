#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

void update_timer();

double get_time_running();

void start_timer();

double get_time_start();

void set_time_at_last_loop();

double get_time_at_last_loop();

void draw_pixels(int left, int top, int width, int height, char bitmap[], bool space_is_transparent);

void draw_border();

void draw_status_display();

void draw_command_window();

void draw_status_item(char string[], int row, int column);

void draw_status_items();

void draw_gui();

void simulation_over_message();

void simulation_quit_message();