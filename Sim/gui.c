#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

static int width;
static int height;

const int vertical = '|';
const int horizontal = '-';
const int corner = '+';

/**
 * draws the border around the terminal
 */
void draw_border() {
    int vertical = '|';
    int horizontal =  '-';
    int corner = '+';

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
 * draws the status display the top of the terminal
 */
void draw_status_display(){
    int status_height = 6;
    int vertical = '|';
    int horizontal =  '-';
    int corner = '+';

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

    int vertical = '-';
    int corner = '+';

    draw_line(1, height - 4, width - 2, height - 4, vertical);
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

    draw_string(x_pos, y_pos, string);
}

/**
 * draws the status items with the current values of the items
 */
void draw_status_items(){
    char student_number[] = "n10009671";
    draw_status_item(student_number, 1, 1);

    char direction[15];
    sprintf(direction, "Direction: %d", robot_direction);
    draw_status_item(direction, 1, 2);

    char battery[13];
    sprintf(battery, "Battery: %d%%", robot_battery);
    draw_status_item(battery, 1, 3);

    char time_running[20];
    /**int minutes;
    int seconds;
    if (time_running == 0){
        minutes = 0;
        seconds = 0;
    }else{
        minutes =  ((int)time_running / 1000) / 60;
        seconds =  ((int)time_running / 1000) % 60;
    }*/

    sprintf(time_running, "Time running: %d", (int)time_running);
    draw_status_item(time_running, 2, 1);

    char weight[11];
    sprintf(weight, "Weight: %dg", robot_weight);
    draw_status_item(weight, 2, 2);

    char rubbish[13];
    sprintf(rubbish, "%d, %d, %d", available_dust, available_slime, available_trash);
    draw_status_item(rubbish, 2, 3);
}


void start_timer(){
    start_time = get_current_time();
}

void update_timer(){
    running_time =  get_current_time() - start_time;
}

void draw_gui(){
    get_screen_size(&width, &height);
    draw_border();
    draw_command_window();
    draw_status_display();
}