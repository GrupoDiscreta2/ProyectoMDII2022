#ifndef _CURSOR_H
#define _CURSOR_H

/**************************** MOVE CURSOR *********************************/

void cursor_up(unsigned int n);
// Moves cursor n lines up from current position
// (if cursor reach to the top, it stop)

void cursor_down(unsigned int n);
// Moves cursor n lines down from current position
// (if cursor reach to the bottom line, it stop)

void cursor_left(unsigned int n);
// Moves cursor in left direction n places from current position

void cursor_right(unsigned int n);
// Moves cursor in right direction n places from current position

void cursor_locate(unsigned int row, unsigned int column);
// The cursor is set in <row>x<column> position

void cursor_save(void);
// Saves current position of cursor

void cursor_restore(void);
// Places cursor on previously saved position

/*************************** COLOR CURSOR ********************************/

void cursor_no_color(void);
// Restore default color

/************************ FOREGROUND COLOR ****/

void cursor_black(void);
// Set foreground black color

void cursor_blue(void);
// Set foreground blue color

void cursor_green(void);
// Set foreground green color

void cursor_cyan(void);
// Set foreground cyan color (~ light blue)

void cursor_red(void);
// Set foreground red color

void cursor_gold(void);
// Set foreground yellow color

void cursor_gray(void);
// Set foreground gray color

void cursor_white(void);
// Set white color (full white)

void cursor_rgb(unsigned int red, unsigned int green, unsigned int blue);
/*
 * Set foreground color with red, green, blue components. The red/green/blue
 * values must be a number in range [0, 255]. For example:
 *
 * cursor_rgb(255, 0, 0); -------> Sets full red color (light red)
 * cursor_rgb(128, 0, 0); -------> Sets middle red color
 * cursor_rgb(128, 0, 200); -----> Sets middle violet color
 * cursor_rgb(255, 255, 255); ---> Sets full white
 *
 *
 */

/************************ BACKGROUND COLOR ****/

void cursor_black_bg(void);
// Set background black color

void cursor_blue_bg(void);
// Set background blue color

void cursor_green_bg(void);
// Set background green color

void cursor_cyan_bg(void);
// Set background cyan color (~ light blue)

void cursor_red_bg(void);
// Set background red color

void cursor_gold_bg(void);
// Set background yellow color

void cursor_gray_bg(void);
// Set background gray color

void cursor_rgb_bg(unsigned int red, unsigned int green, unsigned int blue);
/*
 * Set background color with red, green, blue components. The red/green/blue
 * values must be a number in range [0, 255].
 *
 */

/********************************* ERASE **********************************/

void cursor_cls();
// Clears the screen

#endif

