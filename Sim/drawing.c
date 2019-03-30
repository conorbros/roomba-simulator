#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

int width;
int height;

void draw_pixels(int left, int top, int width, int height, char bitmap[], bool space_is_transparent){
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            if(bitmap[i+j*width] != ' '){
                draw_char(left+i, top+j, bitmap[i+j*width]);
            }else if(!space_is_transparent){
                draw_char(left+i, top+j, ' ');
            }
        }
    }
}