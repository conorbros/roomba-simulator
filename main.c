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

int available_dust;
int available_slime;
int available_trash;


void draw_border() {
    int w;
    int h;

    int vertical = '|';
    int horizontal =  '-';
    int corner = '+';

    get_screen_size(&w, &h);

    draw_line(0, 0, 0, h - 1, vertical);
    draw_line(0, 0, w - 2, 0, horizontal);

    draw_line(1, h - 1, w - 1, h - 1, horizontal);
    draw_line(w - 1, 1, w - 1, h - 1, vertical);

    draw_char(0, 0, corner);
    draw_char(0, h -1 , corner);
    draw_char(w - 1, 0, corner);
    draw_char(w - 1, h - 1, corner);
}

void draw_student_number(){
    char student_number[] = "n10009671";
    draw_string(20, 2, student_number);
}

void draw_robot_direction_status(){
    char direction[15];
    sprintf(direction, "Direction: %d", robot_direction);
    draw_string(67, 2, direction);
}

void draw_robot_battery_life(){
    char battery[13];
    sprintf(battery, "Battery: %d%%", robot_battery);
    draw_string(118, 2, battery);
}

void draw_time_since_reset(){
    char time_running[20];
    sprintf(time_running, "Time running: 00:00");
    draw_string(15, 5, time_running);
}

void draw_robot_weight(){
    char weight[11];
    sprintf(weight, "Weight: %dg", robot_weight);
    draw_string(67, 5, weight);
}

void draw_available_rubbish(){
    char rubbish[13];
    sprintf(rubbish, "%d, %d, %d", available_dust, available_slime, available_trash);
    draw_string(121, 5, rubbish);
}

void draw_status_display(){
    int w = 150;
    int h = 50;

    int status_height = 6;

    int vertical = '|';
    int horizontal =  '-';
    int corner = '+';

    get_screen_size(&w, &h);

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

void draw_command_window(){
    int w, h;

    int vertical = '-';
    int corner = '+';

    get_screen_size(&w, &h);

    draw_line(1, h - 4, w - 2, h - 4, vertical);
    draw_char(0, h - 4, corner);
    draw_char(w - 1, h - 4, corner);
}


void init_robot(){
    robot_battery = 100;
    robot_weight = 0;
}

void setup () {
    init_robot();

    draw_border();
    draw_status_display();
    draw_command_window();

    draw_student_number();
    draw_robot_direction_status();
    draw_robot_battery_life();
    draw_robot_weight();
    draw_time_since_reset();
    draw_available_rubbish();
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
