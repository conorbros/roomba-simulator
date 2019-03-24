#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

// Insert other functions here, or include header files

int robot_weight;
int robot_battery;
int robot_direction;
int robot_x_pos;
int robot_y_pos;
bool return_to_base;

int available_dust;
int available_slime;
int available_trash;


void draw_border(int w, int h) {
    int vertical = '|';
    int horizontal =  '-';
    int corner = '+';

    draw_line(0, 0, 0, h - 1, vertical);
    draw_line(0, 0, w - 2, 0, horizontal);

    draw_line(1, h - 1, w - 1, h - 1, horizontal);
    draw_line(w - 1, 1, w - 1, h - 1, vertical);

    draw_char(0, 0, corner);
    draw_char(0, h - 1 , corner);
    draw_char(w - 1, 0, corner);
    draw_char(w - 1, h - 1, corner);
}

void draw_status_display(int w, int h){
    int status_height = 6;
    int vertical = '|';
    int horizontal =  '-';
    int corner = '+';

    draw_line(1, status_height, w - 2, status_height, horizontal);
    draw_line(1, status_height / 2, w - 2,  status_height / 2, horizontal);

    draw_line(w / 3 , 1, w / 3, status_height - 1, vertical);
    draw_line(w / 3 * 2, 1, w / 3 * 2, status_height - 1, vertical);

    draw_char(0, status_height, corner);
    draw_char(w - 1, status_height, corner);
    draw_char(0, status_height / 2, corner);
    draw_char(w - 1, status_height / 2, corner);

    draw_char(w / 3, 0, corner);
    draw_char(w / 3, status_height / 2, corner);
    draw_char(w / 3, status_height, corner);
    draw_char(w / 3 * 2, 0, corner);
    draw_char(w / 3 * 2, status_height /2, corner);
    draw_char(w / 3 * 2, status_height, corner);
}

void draw_status_item(char string[], int row, int column, int w){
    int y_pos;
    int offset = strlen(string) / 2;
    int x_pos = ((w / 3) * column) - ((w / 3) / 2) - offset;

    if (row == 1) y_pos = 2;
    if (row == 2) y_pos = 5;

    draw_string(x_pos, y_pos, string);
}

void draw_status_items(int w){
    char student_number[] = "n10009671";
    draw_status_item(student_number, 1, 1, w);

    char direction[15];
    sprintf(direction, "Direction: %d", robot_direction);
    draw_status_item(direction, 1, 2, w);

    char battery[13];
    sprintf(battery, "Battery: %d%%", robot_battery);
    draw_status_item(battery, 1, 3, w);

    char time_running[20];
    sprintf(time_running, "Time running: 00:00");
    draw_status_item(time_running, 2, 1, w);

    char weight[11];
    sprintf(weight, "Weight: %dg", robot_weight);
    draw_status_item(weight, 2, 2, w);

    char rubbish[13];
    sprintf(rubbish, "%d, %d, %d", available_dust, available_slime, available_trash);
    draw_status_item(rubbish, 2, 3, w);
}

void draw_command_window(int w, int h){

    int vertical = '-';
    int corner = '+';

    draw_line(1, h - 4, w - 2, h - 4, vertical);
    draw_char(0, h - 4, corner);
    draw_char(w - 1, h - 4, corner);
}

void draw_robot(int direction){

}

void init_robot(){
    robot_battery = 100;
    robot_weight = 0;
    robot_x_pos = 75, robot_y_pos = 25;
    return_to_base = false;
}

void setup () {
    int h;
    int w;
    get_screen_size(&w, &h);

    init_robot();

    draw_border(w, h);
    draw_status_display(w, h);
    draw_command_window(w, h);
    draw_status_items(w);
}

void loop() {

}

int main() {
    setup_screen();
    setup();
    show_screen();
    while ( 1/* Insert termination conditions here */ ) {
        loop();
       // timer_pause( /* Insert delay expression here. */ );

    }

    return 0;
}
