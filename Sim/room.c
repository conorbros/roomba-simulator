#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

#include "helpers.h"
#include "robot.h"

static int width;
static int height;

static int charging_station_x_position;
static int charging_station_y_position;

static int dust_x_positions[1000];
static int dust_y_positions[1000];
static int dust_count = 0;
static int dust_weight = 1;

static int slime_x_positions[10];
static int slime_y_positions[10];
static int slime_count = 0;
static int slime_side = 5;
static int slime_weight = 5;

static int trash_x_positions[5];
static int trash_y_positions[5];
static int trash_count = 0;
static int trash_weight = 20;
static int trash_width = 11;
static int trash_height = 6;

static char * dust = ".";

static char * slime =
    "  ~  "
    " ~~~ "
    "~~~~~"
    " ~~~ "
    "  ~  ";

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

/**
 *  Returns a random int between the supplied min and max
 *
 *  Parameters:
 *      min: the lower limit of the random
 *      max: the upper limit of the max
 *
 *  Returns:
 *      A random int between the min and max
 */
int random_int(int min, int max){
    return (rand() % (max + 1 - min)) + min;
}

/**
 *  Determines if the supplied pixel array overlaps with the robot
 *
 *  Parameters:
 *      x: the left most x coordinate of the pixel array
 *      y: the top most y coordinate of the pixel array
 *      w: the width of the pixel array
 *      h: the height of the pixel array
 *      pixels: the pixel array
 *
 *  Returns:
 *      true if overlap, false if not
 */
bool robot_overlap(int x, int y, int w, int h, char pixels[]){
    if(pixel_collision(x, y, w, h, pixels,
        get_robot_x_pos(), get_robot_y_pos(), 9, 9, get_robot())) return true;
    return false;
}

/**
 *  Determines if the supplied pixel array overlaps with the charging station
 *
 *  Parameters:
 *      x: the left most x coordinate of the pixel array
 *      y: the top most y coordinate of the pixel array
 *      w: the width of the pixel array
 *      h: the height of the pixel array
 *      pixels: the pixel array
 *
 *  Returns:
 *      true if overlap, false if not
 */
bool charging_station_overlap(int x, int y, int w, int h, char pixels[]){
    if(pixel_collision(x, y, w, h, pixels,
        charging_station_x_position, charging_station_y_position, 9, 3, charging_station )) return true;
    return false;
}

/**
 *  Determines if the supplied pixel array overlaps with any of the dust
 *
 *  Parameters:
 *      x: the left most x coordinate of the pixel array
 *      y: the top most y coordinate of the pixel array
 *      w: the width of the pixel array
 *      h: the height of the pixel array
 *      pixels: the pixel array
 *
 *  Returns:
 *      true if overlap, false if not
 */
bool dust_overlap(int x, int y, int w, int h, char pixels[], int dust_c){
    for(int i = 0; i < dust_c; i++){
        if(pixel_collision(x, y, w, h, pixels,
            dust_x_positions[i], dust_y_positions[i], 1, 1, dust)) return true;
    }
    return false;
}

/**
 *  Determines if the supplied pixel array overlaps with any of the slime
 *
 *  Parameters:
 *      x: the left most x coordinate of the pixel array
 *      y: the top most y coordinate of the pixel array
 *      w: the width of the pixel array
 *      h: the height of the pixel array
 *      pixels: the pixel array
 *
 *  Returns:
 *      true if overlap, false if not
 */
bool slime_overlap(int x, int y, int w, int h, char pixels[], int slime_c){
    for(int i = 0; i < slime_c; i++){
         if(pixel_collision(x, y, w, h, pixels,
            slime_x_positions[i], slime_y_positions[i], slime_side, slime_side, slime)) {
                return true;
         };
    }
    return false;
}

/**
 *  Determines if the supplied pixel array overlaps with any of the trash
 *
 *  Parameters:
 *      x: the left most x coordinate of the pixel array
 *      y: the top most y coordinate of the pixel array
 *      w: the width of the pixel array
 *      h: the height of the pixel array
 *      pixels: the pixel array
 *
 *  Returns:
 *      true if overlap, false if not
 */
bool trash_overlap(int x, int y, int w, int h, char pixels[], int trash_c){
    for(int k = 0; k < trash_c; k++){
        if(pixel_collision(x, y, w, h, pixels,
            trash_x_positions[k], trash_y_positions[k], trash_width, trash_height, trash)) {
                return true;
        }
    }
    return false;
}


/**
 *  Determines if the supplied pixel array overlaps with any of the slime
 *
 *  Parameters:
 *      x: the left most x coordinate of the pixel array
 *      y: the top most y coordinate of the pixel array
 *      w: the width of the pixel array
 *      h: the height of the pixel array
 *      pixels: the pixel array
 *
 *  Returns:
 *      true if overlap, false if not
 */
bool object_overlap(int x, int y, int w, int h, char pixels[], int dust_c, int slime_c, int trash_c){
    if(dust_overlap(x, y, w, h, pixels, dust_c)) return true;

    if(slime_overlap(x, y, w, h, pixels, slime_c)) return true;

    if(trash_overlap(x, y, w, h, pixels, trash_c)) return true;

    if(robot_overlap(x, y, w, h, pixels)) return true;

    if(charging_station_overlap(x, y, w, h, pixels)) return true;

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


/**
 *  Drops one dust at the supplied x,y coordinate
 *
 *  Parameters:
 *      x: the x coordinate to drop dust at
 *      y: the y coordindate to drop dust at
 *
 */
void drop_dust(int x, int y){
    if(dust_count == 1000) return;
    if(object_overlap(x, y, 1, 1, dust, dust_count, slime_count, trash_count)) return;

    dust_x_positions[dust_count] = x;
    dust_y_positions[dust_count] = y;
    dust_count++;
}


/**
 *  Gets an input to drop dust and ensures it is in the range of the border
 */
void drop_dust_input(){
    int x_pos = get_int("Drop dust at x position: ");
    if(x_pos < 1) x_pos = 1;
    if(x_pos > width - 2) x_pos = width - 2;

    int y_pos = get_int("Drop dust at y position: ");
    if(y_pos < 8) y_pos = 8;
    if(y_pos > height - 4) y_pos = height - 4;

    drop_dust(x_pos, y_pos);
}


/**
 *  "Pickups" dust by removing it from the array and applying the weight to the robot's weight
 *
 *  Parameters:
 *      index: the dust array index to pickup
 */
void pickup_dust(int index){
    for(int i = index; i < dust_count - 1; i++) {
        dust_x_positions[i] = dust_x_positions[i + 1];
        dust_y_positions[i] = dust_y_positions[i + 1];
    }
    dust_count--;
    robot_pickup_rubbish(dust_weight);
}


/**
 *  Draws all the dust currently on the floor
 */
void draw_dust(){
    for(int i = 0; i < dust_count; i++){
        draw_pixels(dust_x_positions[i], dust_y_positions[i], 1, 1, dust, true);
    }
}


/**
 *  Initializes the dust, will replace the dust's location with a new one if it collides with an already placed piece of rubbish or object
 */
void init_dust(){
    int x_pos;
    int y_pos;

    for(int i = 0; i < dust_count; i++){
        do{
            x_pos = random_int(1, width - 2);
            y_pos = random_int(7, height - 4);
        }while(object_overlap(x_pos, y_pos, 2, 2, dust, i, slime_count, trash_count));

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

 /**
 *  Drops one slime at the supplied x,y coordiante
 *
 *  Parameters:
 *      x: the x coordinate to drop slime at
 *      y: the y coordinate to drop slime at
 *
 */
void drop_slime(int x, int y){
    if (slime_count == 10) return;
    slime_x_positions[slime_count] = x;
    slime_y_positions[slime_count] = y;
    slime_count++;
}

 /**
 *  Gets an input to drop slime and ensures it is in the range of the border
 */
void drop_slime_input(){
    int x_pos = get_int("Drop slime at x position: ");
    if(x_pos < 1 ) x_pos = 1;
    if(x_pos > (width - 1) - slime_side) x_pos = (width - 1) - slime_side;

    int y_pos = get_int("Drop slime at y position: ");
    if (y_pos < 8) y_pos = 8;
    if (y_pos > (height - 3) - slime_side) y_pos = (height - 3) - slime_side;

    drop_slime(x_pos, y_pos);
}

/**
 *  "Pickups" slime by removing it from the array and applying the weight to the robot's weight
 *
 *  Parameters:
 *      index: the slime array index to pickup
 */
void pickup_slime(int index){
    for(int i = index; i < slime_count - 1; i++){
        slime_x_positions[i] = slime_x_positions[i + 1];
        slime_y_positions[i] = slime_y_positions[i + 1];
    }
    slime_count--;
    robot_pickup_rubbish(slime_weight);
}

/**
 *  Draws all the dust currently on the floor
 */
void draw_slime(){
    for(int i = 0; i < slime_count; i++){
        draw_pixels(slime_x_positions[i], slime_y_positions[i], slime_side, slime_side, slime, true);
    }
}

/**
 *  Initializes the slime, will replace the slime's location with a new one if it collides with an already placed piece of rubbish or object
 */
void init_slime(){
    int x_pos;
    int y_pos;

    for(int i = 0; i < slime_count; i++){
        do{
            x_pos = random_int(1, width - 1 - slime_side);
            y_pos = random_int(7, height - 3 - slime_side);
        }while(object_overlap(x_pos, y_pos, slime_side, slime_side, slime, 0, i, trash_count));

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

/**
 *  Draws all the trash currently on the floor
 */
void draw_trash(){
    for(int i = 0; i < trash_count; i++){
        draw_pixels(trash_x_positions[i], trash_y_positions[i], trash_width, trash_height, trash, true);
    }
}

/**
 *  Determines if the supplied trash position will overlap with already placed trash
 *
 *  Parameters:
 *      x: the possible x coordinate of a new piece of trash
 *      y: the possible y coorindate of a new piece of trash
 *  Returns:
 *      true if collision, false if not
 */
bool trash_will_overlap(int x, int y, int trash_count){
    for(int i = 0; i < trash_count; i++){
        if(pixel_collision(x, y, trash_width, trash_height, trash,
            trash_x_positions[i], trash_y_positions[i], trash_width, trash_height, trash)){
                return true;
            }
    }
    return false;
}

 /**
 *  Drops one trash at the supplied x,y coordiante
 *
 *  Parameters:
 *      x: the x coordinate to drop trash at
 *      y: the y coordinate to drop trash at
 *
 */
void drop_trash(int x, int y){
    if(trash_count == 5) return;

    trash_x_positions[trash_count] = x;
    trash_y_positions[trash_count] = y;

    trash_count++;
}

 /**
 *  Gets an input to drop trash and ensures it is in the range of the border
 */
void drop_trash_input(){
    int x_pos = get_int("Drop trash at x position: ");
    if (x_pos < 1) x_pos = 1;
    if (x_pos > (width - 1) - trash_width) x_pos = (width - 1) - trash_width;

    int y_pos = get_int("Drop trash at y position: ");
    if (y_pos < 8) y_pos = 8;
    if (y_pos > (height - 3) - trash_height) y_pos = (height - 4) - trash_height;

    drop_trash(x_pos, y_pos);
}

/**
 *  "Pickups" trash by removing it from the array and applying the weight to the robot's weight
 *
 *  Parameters:
 *      index: the trash array index to pickup
 */
void pickup_trash(int index){
    for(int i = index; i < trash_count - 1; i++){
        trash_x_positions[i] = trash_x_positions[i + 1];
        trash_y_positions[i] = trash_y_positions[i + 1];
    }

    trash_count--;

    robot_pickup_rubbish(trash_weight);
}

/**
 *  Initializes the trash, will replace the trash's location with a new one if it collides with an already placed piece of rubbish or object
 */
void init_trash(){
    int x_pos;
    int y_pos;

    for(int i = 0; i < trash_count; i++){

        do{
            x_pos = random_int(1, width - 1 - trash_width);
            y_pos = random_int(7, height - 3 - trash_height);
        }while(trash_will_overlap(x_pos, y_pos, i));

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

/**
 * draws the charging station and rubbish
 */
void draw_room(){
    draw_charging_station();
    draw_trash();
    draw_slime();
    draw_dust();
}

 /**
 *  Initializes the trash with the supplied counts of each
 *
 *  Parameters:
 *      dust: the dust count
 *      slime: the slime count
 *      trash: the trash count
 */
void init_rubbish(int dust, int slime, int trash){
    trash_count = trash;
    init_trash();
    slime_count = slime;
    init_slime();
    dust_count = dust;
    init_dust();
}

 /**
 *  Initializes the room and supplies the terminal height and width to the program
 */
void init_room(){
    srand(time(0));
    get_screen_size(&width, &height);
    charging_station_x_position = width / 2 - 5;
    charging_station_y_position = 7;
}
