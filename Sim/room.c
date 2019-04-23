#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include <drawing.h>
#include <helpers.h>
#include <robot.h>
#include <misc.h>

static int width;
static int height;

static int charging_station_x_position;
static int charging_station_y_position;

static int dust_x_positions[1000];
static int dust_y_positions[1000];
static int dust_count;

/*
static int slime_x_positions[10];
static int slime_y_positions[10];
static int slime_count;

static int trash_x_positions[5];
static int trash_y_positions[5];
static int trash_count;
*/
static char * dust = ".";

static char * charging_station =
    "#########"
    "#########"
    "#########";


int get_dust_count(){
    return dust_count;
}

char * get_dust(){
    return dust;
}

int * get_dust_x_positions(){
    return dust_x_positions;
}

int * get_dust_y_positions(){
    return dust_y_positions;
}

bool dust_will_overlap(int x, int y, int count){
    for(int i = 0; i < count; i++){
        if(dust_x_positions[i] == x && dust_y_positions[i] == y) return true;
    }

    if (pixel_collision(x, y, 1, 1, dust,
        charging_station_x_position, charging_station_y_position, 9, 3, charging_station)){
            return true;
        };
    if(pixel_collision(x, y, 1, 1, dust,
        get_robot_x_pos(), get_robot_y_pos(), 9, 9, get_robot())){
            return true;
        }
    return false;
}

void drop_dust(int x, int y){
    if(dust_count == 1000) return;
    if(dust_will_overlap(x, y, dust_count)) return;

    dust_x_positions[dust_count] = x;
    dust_y_positions[dust_count] = y;
    dust_count++;
}

void drop_dust_input(){
    int x_pos = get_int("Drop dust at x position: ");
    if(x_pos < 1) x_pos = 1;
    if(x_pos > width - 2) x_pos = width - 2;

    int y_pos = get_int("Drop dust at y position: ");
    if(y_pos < 8) y_pos = 8;
    if(y_pos > height - 4) y_pos = height - 4;

    drop_dust(x_pos, y_pos);
}

void draw_dust(){
    for(int i = 0; i < dust_count; i++){
        draw_char(dust_x_positions[i], dust_y_positions[i], '.');
    }
}

void init_dust(){
    int x_pos;
    int y_pos;

    for(int i = 0; i < dust_count; i++){
        x_pos = random_range(1, width - 2);
        y_pos = random_range(8, height - 5);

        while(i > 0){
            if(dust_will_overlap(x_pos, y_pos, i)){
                x_pos = random_range(1, width - 2);
                y_pos = random_range(8, height - 5);
            }else{
                break;
            }
        }

        dust_x_positions[i] = x_pos;
        dust_y_positions[i] = y_pos;
    }
}


int get_charging_station_x_position(){
    return charging_station_x_position;
}

int get_charging_station_y_position(){
    return charging_station_y_position;
}

char* get_charging_station(){
    return charging_station;
}

void draw_charging_station(){
    draw_pixels(charging_station_x_position, charging_station_y_position, 9, 3, charging_station, false);
}

void draw_room(){
    draw_charging_station();
    draw_dust();
}

void init_room(int dust){
    get_screen_size(&width, &height);
    charging_station_x_position = width/2 - 5;
    charging_station_y_position = 7;

    dust_count = dust;
    init_dust();
}

