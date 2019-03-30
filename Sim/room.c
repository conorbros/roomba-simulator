#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

static int dust_count;
static int slime_count;
static int trash_count;

void draw_charging_station(int width){
    char * charging_station =
    "#########"
    "#       #"
    "#########";

    draw_pixels(width / 2 - 4, 7, 9, 3, charging_station, false);
}


int get_dust_count(){
    return dust_count;
}

void drop_dust(){

}

int get_slime_count(){
    return slime_count;
}

void drop_slime(){

}

int get_trash_count(){
    return trash_count;
}

void drop_trash(){

}

void reset_rubbish(){
    dust_count = 0;
    slime_count = 0;
    trash_count = 0;
}

void draw_room(){

}
