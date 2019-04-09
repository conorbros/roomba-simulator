#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include <robot.h>
#include <drawing.h>
#include <main.h>
#include <helpers.h>
#include <room.h>

static int width;
static int height;

const int vertical = '|';
const int horizontal = '-';
const int corner = '+';

static double time_running;
static double time_at_last_loop;
static double time_start;

int get_screen_width(){
    return width;
}

int get_screen_height(){
    return height;
}

void update_timer(){
    time_running = get_current_time() - time_start;
}

double get_time_running(){
    return time_running;
}

void start_timer(){
    time_start = get_current_time();
}

double get_time_start(){
    return time_start;
}

void set_time_at_last_loop(){
    time_at_last_loop = time_running;
}

double get_time_at_last_loop(){
    return time_at_last_loop;
}

/**
 * draws the border around the terminal
 */
void draw_border() {

    draw_line(0, 0, 0, height - 1, vertical);
    draw_line(0, 0, width - 2, 0, horizontal);

    draw_line(1, height - 1, width - 1, height - 1, horizontal);
    draw_line(width - 1, 1, width - 1, height - 1, vertical);

    draw_char(0, 0, corner);
    draw_char(0, height - 1 , corner);
    draw_char(width - 1, 0, corner);
    draw_char(width - 1, height - 1, corner);
}

/**
 * draws the status display borders at the top of the terminal
 */
void draw_status_display(){
    int status_height = 6;

    draw_line(1, status_height, width - 2, status_height, horizontal);
    draw_line(1, status_height / 2, width - 2,  status_height / 2, horizontal);

    draw_line(width / 3 , 1, width / 3, status_height - 1, vertical);
    draw_line(width / 3 * 2, 1, width / 3 * 2, status_height - 1, vertical);

    draw_char(0, status_height, corner);
    draw_char(width - 1, status_height, corner);
    draw_char(0, status_height / 2, corner);
    draw_char(width - 1, status_height / 2, corner);

    draw_char(width / 3, 0, corner);
    draw_char(width / 3, status_height / 2, corner);
    draw_char(width / 3, status_height, corner);
    draw_char(width / 3 * 2, 0, corner);
    draw_char(width / 3 * 2, status_height /2, corner);
    draw_char(width / 3 * 2, status_height, corner);
}

/**
 * draws the command window at the bottom of the terminal
 */
void draw_command_window(){
    draw_line(1, height - 4, width - 2, height - 4, horizontal);
    draw_char(0, height - 4, corner);
    draw_char(width - 1, height - 4, corner);
}

/**
 * Draws a status item using the content and position parameters supplied
 * Parameters:
 *      string[]: the content of the status item
 *      row: the row that the status item is the be displayed in
 *      column: the column that the status item is to be displayed in
 */
void draw_status_item(char string[], int row, int column){
    int y_pos;
    int offset = strlen(string) / 2;
    int x_pos = ((width / 3) * column) - ((width / 3) / 2) - offset;

    if (row == 1) y_pos = 2;
    if (row == 2) y_pos = 5;

    draw_formatted(x_pos, y_pos,"%s", string);
}

/**
 * draws the status items with the current values of the items
 */
void draw_status_items(){
    char student_number[] = "n10009671";
    draw_status_item(student_number, 1, 1);

    char direction[15];
    sprintf(direction, "Direction: %d", (int)get_robot_direction());
    draw_status_item(direction, 1, 2);

    char battery[13];
    sprintf(battery, "Battery: %d%%", get_robot_battery());
    draw_status_item(battery, 1, 3);

    char time_output[20];
    double diff = get_time_running();
    int minutes = (int) diff / 60;
    int seconds = (int) diff % 60;

    if (minutes < 10 && seconds < 10){
        sprintf(time_output, "Time running: 0%d:0%d", minutes, seconds);
    } else if (minutes < 10){
        sprintf(time_output, "Time running: 0%d:%d", minutes, seconds);
    } else if (seconds < 10){
        sprintf(time_output, "Time running: %d:0%d", minutes, seconds);
    } else if (minutes == 0){
        sprintf(time_output, "Time running: 00:%d", seconds);
    }
    draw_status_item(time_output, 2, 1);

    char weight[11];
    sprintf(weight, "Weight: %dg", 0);
    draw_status_item(weight, 2, 2);

    char rubbish[13];
    sprintf(rubbish, "%d, %d, %d", get_dust_count(), 0, 0);
    draw_status_item(rubbish, 2, 3);
}

void draw_gui(){
    get_screen_size(&width, &height);
    draw_border();
    draw_command_window();
    draw_status_display();
    draw_status_items();
}


void fill_rect(int x1, int y1, int x2, int y2, char c){
    if (x2 - x1 < 0 || y2 - y1 < 0) return;
    for (int i = x1; i <= x2; i++){
        for (int j = y1; j <= y2; j++){
            draw_char(i, j, c);
        }
    }
}

void draw_status_rect(){
    draw_gui();
    draw_room();
    draw_robot();
    draw_rect((width / 2) - 40, (height / 2) - 10, (width / 2) + 40, (height / 2) + 10, '#');
    fill_rect((width / 2) - 39, (height / 2) - 9, (width / 2) + 39, (height / 2) + 9, ' ');
}

void simulation_over_message(){
    draw_status_rect();
    draw_string((width / 2) - 23, height / 2, "SIMULATION OVER! Press r to reset or q to quit.");
    show_screen();

    int input;
    while(1){
        input = get_char();
        if (input == 'r'){
            reset();
            break;
        }
        if (input == 'q'){
            quit();
            break;
        }
    }
}

void simulation_quit_message(){
    draw_status_rect();
    draw_string((width / 2) - 21, height / 2, "SIMULATION ENDING... Press any key to exit");
    show_screen();

    while(!wait_char()){
        continue;
    }
}