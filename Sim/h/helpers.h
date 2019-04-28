#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <cab202_graphics.h>

void draw_rect(int left, int top, int right, int bottom, int ch);
void draw_formatted_lines(int x0, int y0, const char * format, ...);
void erase_row(int y);
int get_chars(char * prompt, char * buffer, const int max_len);
int get_int(char * prompt);
bool pixel_collision(int x0, int y0, int w0, int h0, char pixels0[], int x1, int y1, int w1, int h1, char pixels1[]);
bool border_overlap(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void draw_pixels(int left, int top, int width, int height, char bitmap[], bool space_is_transparent);