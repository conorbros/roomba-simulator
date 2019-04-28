#include <math.h>
#include <stdio.h>
#include <string.h>
#include <cab202_graphics.h>
#include <ctype.h>

/**
 *  Draws the outline of a rectangle.
 *
 *  Parameters:
 *      left: the horizontal offset of the left edge of the shape.
 *      top: the vertical offset of the top edge of the shape.
 *      right: the horizontal offset of the right edge of the shape.
 *      bottom: the vertical offset of the bottom edge of the shape.
 */
void draw_rect(int left, int top, int right, int bottom, int ch) {
	draw_line( left, top, right, top, ch);
	draw_line( left, bottom, right, bottom, ch);
	draw_line( left, top, left, bottom, ch);
	draw_line( right, top, right, bottom,ch);
}

/**
 *  Draws formatted text, starting at the specified location, and spreading
 *  across multiple lines if necessary. The rendered text is added to the
 *  zdk_screen buffer, but remains unseen until the next
 *  invocation of show_screen().
 *
 *  Input:
 *      x - The horizontal offset at which the first character is to be
 *          drawn. See draw_string() for further interpretation of this value.
 *
 *      y - The vertical offset at which the first character is to be drawn.
 *          See draw_string() for further interpretation of this value.
 *
 *      format - A string which is structured according to the requirements
 *          of sprintf() which will be used in conjunction with any subsequent
 *          arguments to generate the text for display.
 *
 *      ... - An optional sequence of additional arguments.
 *
 *  Output: void.
 *
 *  Notes:    Total length of generated text must be less than 1000 characters.
 *
 *  See also: Standard library function, sprintf().
 */
void draw_formatted_lines(int x0, int y0, const char * format, ...) {
    const int BUFF_SIZE = 1000;
    char buffer[BUFF_SIZE];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFF_SIZE, format, args);

    int x = x0;
    int y = y0;

    for (int i = 0; (i < BUFF_SIZE) && (buffer[i] != 0); i++) {
        char ch = buffer[i];

        if (ch == '\n') {
            // Linefeed: advance to start of next line.
            x = x0;
            y++;
        }
        else {
            // Draw a normal char
            draw_char(x, y, ch);
            x++;
        }
    } // End for
} // End draw_formatted_lines

/**
 *  Erases the designated row of the terminal window by drawing spaces on it.
 *
 *  Parameters:
 *      y: the vertical offset of the row to be erased.
 */
void erase_row(int y) {
	draw_line( 0, y, screen_width() - 1, y, ' ');
}

/**
 *  Use the bottom two rows of the terminal window as an input dialog.
 *  Display a prompt, then consume characters from standard input until
 *  a value with code less than that of ' ' (ASCII 32) is encountered.
 *  Values are stored at the end of a zero-terminated string which is
 *  accumulated in buffer.
 *
 *  Parameters:
 *      prompt: a character array containing the text to display.
 *
 *      buffer: the address of a character array where the character data
 *          will be stored.
 *
 *      max_len: the maximum number of characters that can be stored in the
 *          buffer (including the zero-terminator).
 *
 *  Returns:
 *      The length of the accumulated line of input data.
 */
int get_chars(char * prompt, char * buffer, const int max_len) {
    int len = 0, w, h;
    const char cursor = '_';

    buffer[0] = 0;

    get_screen_size(&w, &h);
    erase_row(h - 2);
    erase_row(h - 1);
    draw_string((w - strlen(prompt)) / 2, h - 2, prompt);
    draw_char((w - 1) / 2, h - 1, cursor);
    show_screen();

    while (len < max_len - 1) {
        int ch = wait_char();

		if (ch < ' ') break;

		buffer[len] = ch;
        len++;
        buffer[len] = 0;

        int x = (w - len) / 2;
        draw_string(x, h - 1, buffer);
        draw_char(x + len, h - 1, cursor);
        show_screen();

    } // End while

    return len;
} // End get_chars}

/**
 *  Use the bottom two rows of the terminal window as an input dialog.
 *  Display a prompt, then consume characters from standard input until
 *  a non-digit is encountered. An unsigned integer value accumulates
 *  digit-by-digit as each character is received.
 *
 *  Parameters:
 *      prompt: a character array containing the text to display.
 *
 *  Returns:
 *      The accumulated numeric value. This will be 0 if no digits were
 *      encountered.
 */
int get_int(char * prompt) {
    int w, h, z = 0, digits = 0;
    const char cursor = '_';

	get_screen_size(&w, &h);
    erase_row(h - 2);
    erase_row(h - 1);
    draw_string((w - strlen(prompt)) / 2, h - 2, prompt);
    draw_char((w - 1) / 2, h - 1, cursor);
    show_screen();

	while (1) {
        int digit = wait_char();

        if (!isdigit(digit)) break;

        z = z * 10 + (digit - '0');
        digits++;

        int x = (w - digits) / 2;
        draw_int(x, h - 1, z);
        draw_char(x + digits, h - 1, cursor);
        show_screen();
    } // End while

    return z;
} // End get_int

/**
 *  Determines whether the coordinate in the supplied pixel array is opaque or not
 */
bool is_opaque(int x, int y, int x0, int y0, int w0, int h0, char pixels[])
{
    return x >= x0 && x < x0 + w0
        && y >= y0 && y < y0 + h0
        && pixels[(x-x0) + (y-y0)*w0] != ' ';
}

/**
 *  Determines whether there is a collision between any pixels in the supplied pixel arrays.
 *
 *  Parameters:
 *      x0: the left most x coordinate of the first pixel array
 *      y0: the top most y coordinate of the first pixel array
 *      w0: the width of the first pixel array
 *      h0: the height of the first pixel array
 *      pixels0: the first pixel array
 *
 *      x1: the left most x coordinate of the second pixel array
 *      y1: the top most y coordinate of the second pixel array
 *      w1: the width of the second pixel array
 *      h1: the height of the second pixel array
 *      pixels1: the second pixel array
 *
 *  Returns:
 *      true if collision, false if not
 */
bool pixel_collision(int x0, int y0, int w0, int h0, char pixels0[],
    int x1, int y1, int w1, int h1, char pixels1[])
{
    for ( int j = 0; j < h0; j++ ){
        for (int i = 0; i < w0; i++){
            int x = x0 + i;
            int y = y0 + j;

            if ( is_opaque(x, y, x0, y0, w0, h0, pixels0) && is_opaque(x, y, x1, y1, w1, h1, pixels1)){
                return true;
            }
        }
    }

    return false;
}

/**
 *  Draws the pixel array supplied on the terminal window, starting at the left and top coordinates
 *
 *  Parameters:
 *      left: the left most x coordinate of the pixel array
 *      top: the top most y coorindate of the pixel array
 *      width: the width of the pixel array
 *      height: the height of the pixel array
 *      pixels: the pixel array to be array
 */
void draw_pixels(int left, int top, int width, int height, char pixels[], bool space_is_transparent){
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            if(pixels[i + j * width] != ' '){
                draw_char(left + i, top + j, pixels[i + j * width]);
            }else if(!space_is_transparent){
                draw_char(left + i, top + j, ' ');
            }
        }
    }
}