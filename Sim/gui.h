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

void draw_border();

void draw_status_display();

void draw_command_window();

void draw_status_item(char string[], int row, int column);

void draw_status_items();

void draw_gui();