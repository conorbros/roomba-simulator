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
static int dust_weight = 1;


//change slime limit to 10
static int slime_x_positions[100];
static int slime_y_positions[100];
static int slime_count;
static int slime_side = 5;
static int slime_weight = 5;

static int trash_x_positions[5];
static int trash_y_positions[5];
static int trash_count;
static int trash_weight = 20;
static int trash_width = 11;
static int trash_height = 6;

static char * dust = ".";

static char * slime =
    " ~~~ "
    "~~~~~"
    "~~~~~"
    "~~~~~"
    " ~~~ ";

static char * trash =
    "     &     "
    "    &&&    "
    "   &&&&&   "
    "  &&&&&&&  "
    " &&&&&&&&& "
    "&&&&&&&&&&&";

static char * charging_station =
    "#########"
    "#########"
    "#########";

bool robot_collision(int x, int y, int w, int h, char bitmap[]){
    if(pixel_collision(x, y, w, h, bitmap,
        get_robot_x_pos(), get_robot_y_pos(), 9, 9, get_robot())){
            return true;
    }
    return false;
}

bool rubbish_overlap(int x, int y, int w, int h, char bitmap[], int dust_count, int slime_count, int trash_count){

    for(int i = 0; i < dust_count; i++){
        if(pixel_collision(x, y, w, h, bitmap,
        dust_x_positions[i], dust_y_positions[i], 1, 1, dust)) return true;
    }

    for(int i = 0; i < slime_count; i++){
        if(pixel_collision(x, y, w, h, bitmap,
        slime_x_positions[i], slime_y_positions[i], slime_side, slime_side, slime)) return true;
    }

    for(int i = 0; i < trash_count; i++){
        if(pixel_collision(x, y, w, h, bitmap,
        trash_x_positions[i], trash_y_positions[i], trash_width, trash_height, trash)) return true;
    }

    if(robot_collision(x, y, w, h, bitmap)) return true;

    return false;
}

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

void drop_dust(int x, int y){
    if(dust_count == 1000) return;
    if(rubbish_overlap(x, y, 1, 1, dust, dust_count, slime_count, trash_count)) return;

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

void pickup_dust(int index){
    for(int i = index; i < dust_count - 1; i++) {
        dust_x_positions[i] = dust_x_positions[i + 1];
        dust_y_positions[i] = dust_y_positions[i + 1];
    }

    dust_count--;

    robot_pickup_rubbish(dust_weight);
}

void draw_dust(){
    for(int i = 0; i < dust_count; i++){
        draw_pixels(dust_x_positions[i], dust_y_positions[i], 1, 1, dust, true);
    }
}

void init_dust(){
    int x_pos;
    int y_pos;

    for(int i = 0; i < dust_count; i++){
        x_pos = random_range(1, width - 2);
        y_pos = random_range(8, height - 5);

        while(i > 0){
            if(rubbish_overlap(x_pos, y_pos, 1, 1, dust, dust_count, slime_count, trash_count)){
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

int get_slime_count(){
    return slime_count;
}

char * get_slime(){
    return slime;
}

int get_slime_side(){
    return slime_side;
}


int * get_slime_x_positions(){
    return slime_x_positions;
}

int * get_slime_y_positions(){
    return slime_y_positions;
}

void drop_slime(int x, int y){
    if (slime_count == 10) return;

    slime_x_positions[slime_count] = x;
    slime_y_positions[slime_count] = y;
    slime_count++;
}

void drop_slime_input(){
    int x_pos = get_int("Drop slime at x position: ");
    if(x_pos < 1 ) x_pos = 1;
    if(x_pos > (width - 1) - slime_side) x_pos = (width - 1) - slime_side;

    int y_pos = get_int("Drop slime at y position: ");
    if (y_pos < height - 4) y_pos = height - 4;
    if (y_pos > (height - 4) - slime_side) y_pos = (height - 4) - slime_side;

    drop_slime(x_pos, y_pos);
}

void pickup_slime(int index){
    for(int i = index; i < slime_count; i++){
        slime_x_positions[i] = slime_x_positions[i + 1];
        slime_y_positions[i] = slime_y_positions[i + 1];
    }

    slime_count--;

    robot_pickup_rubbish(slime_weight);
}

void draw_slime(){
    for(int i = 0; i < slime_count; i++){
        draw_pixels(slime_x_positions[i], slime_y_positions[i], slime_side, slime_side, slime, true);
    }
}

void init_slime(){
    int x_pos;
    int y_pos;

    for(int i = 0; i < slime_count; i++){
        x_pos = random_range(1, width - 1 - slime_side);
        y_pos = random_range(8, height - 4 - slime_side);

        while(rubbish_overlap(x_pos, y_pos, slime_side, slime_side, slime, 0, i, trash_count)){
            x_pos = random_range(1, width - 1 - slime_side);
            y_pos = random_range(8, height - 4 - slime_side);
        }

        slime_x_positions[i] = x_pos;
        slime_y_positions[i] = y_pos;
    }
}

int get_trash_count(){
    return trash_count;
}

int get_trash_width(){
    return trash_width;
}

int get_trash_height(){
    return trash_height;
}

char * get_trash(){
    return trash;
}

int * get_trash_x_positions(){
    return trash_x_positions;
}

int * get_trash_y_positions(){
    return trash_y_positions;
}

bool trash_will_overlap(int x, int y, int trash_count){
    for(int i = 0; i < trash_count; i++){
        if(pixel_collision(x, y, trash_width, trash_height, trash,
            trash_x_positions[i], trash_y_positions[i], trash_width, trash_height, trash)){
                return true;
            }
    }
    return false;
}

void drop_trash(int x, int y){
    if(trash_count == 5) return;

    trash_x_positions[trash_count] = x;
    trash_x_positions[trash_count] = y;

    trash_count++;
}

void drop_trash_input(){
    int x_pos = get_int("Drop trash at x position: ");
    if (x_pos < 1) x_pos = 1;
    if (x_pos > (width - 1) - trash_width) x_pos = (width - 1) - trash_width;

    int y_pos = get_int("Drop trash at y position: ");
    if (y_pos > 8) y_pos = 8;
    if (y_pos > (height - 3) - trash_height) y_pos = (height - 4) - trash_height;

    drop_slime(x_pos, y_pos);
}

void pickup_trash(int index){
    for(int i = index; i < trash_count; i++){
        trash_x_positions[i] = trash_x_positions[i + 1];
        trash_y_positions[i] = trash_y_positions[i + 1];
    }

    trash_count--;

    robot_pickup_rubbish(trash_weight);
}

void draw_trash(){
    for(int i = 0; i < trash_count; i++){
        draw_pixels(trash_x_positions[i], trash_y_positions[i],
            trash_width, trash_height, trash, true);
    }
}

void init_trash(){
    int x_pos;
    int y_pos;

    for(int i = 0; i < trash_count; i++){
        x_pos = random_range(1, width - 1 - trash_width);
        y_pos = random_range(8, height - 4 - trash_height);

        while(trash_will_overlap(x_pos, y_pos, i)){
            x_pos = random_range(1, width - 1 - trash_width);
            y_pos = random_range(8, height - 4 - trash_height);
        }

        trash_x_positions[i] = x_pos;
        trash_y_positions[i] = y_pos;
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
    draw_slime();
    draw_trash();
}

void init_rubbish(){
    init_trash();
    init_slime();
    init_dust();
}

void init_room(int dust, int slime, int trash){
    get_screen_size(&width, &height);
    charging_station_x_position = width / 2 - 5;
    charging_station_y_position = 7;
    dust_count = dust;
    slime_count = slime;
    trash_count = trash;
}
