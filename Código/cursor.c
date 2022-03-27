/*
*  This implementation of cursor it's based on ANSI escape codes that terminal
*  emulators usually understands (doesn't work on Windows). For windows users
*  it can be implemented using the <conio.h> library.
*
*/
#include <stdio.h>
#include <assert.h>

// Move cursor ANSI codes
#define ANSI_N_RIGHT "\033[%uC"
#define ANSI_N_LEFT "\033[%uD"
#define ANSI_N_DOWN "\033[%uB"
#define ANSI_N_UP "\033[%uA"
#define ANSI_LOCATE "\033[%u;%uf"
#define ANSI_SAVE_CURSOR "\033[s"
#define ANSI_RESTORE_CURSOR "\033[u"
// Other
#define ANSI_CLS "\033[2J" "\033[0;0H"
//
// ------- Color ANSI codes ---------
//
#define ANSI_NOCOLOR "\033[0m"
// Foreground
#define ANSI_RGB "\033[38;2;%u;%u;%um"
#define ANSI_BLACK "\033[0;30m"
#define ANSI_BLUE "\033[0;34m"
#define ANSI_GREEN "\033[38;2;0;200;0m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_RED  "\033[0;31m"
#define ANSI_GOLD  "\033[0;33m"
#define ANSI_GRAY  "\033[0;37m"
#define ANSI_WHITE "\033[38;2;255;255;255m"
// Background
#define ANSI_BLACK_BG "\033[0;40m"
#define ANSI_BLUE_BG "\033[0;44m"
#define ANSI_GREEN_BG "\033[0;42m"
#define ANSI_CYAN_BG "\033[0;46m"
#define ANSI_RED_BG  "\033[0;41m"
#define ANSI_GOLD_BG  "\033[0;43m"
#define ANSI_GRAY_BG  "\033[0;47m"
#define ANSI_RGB_BG "\033[48;2;%u;%u;%um"


void cursor_up(unsigned int n) {
    if (n > 0) {
        printf(ANSI_N_UP, n);
    }
}

void cursor_down(unsigned int n) {
    if (n > 0) {
        printf(ANSI_N_DOWN, n);
    }
}

void cursor_left(unsigned int n) {
    if (n > 0) {
        printf(ANSI_N_LEFT, n);
    }
}

void cursor_right(unsigned int n) {
    if (n > 0) {
        printf(ANSI_N_RIGHT, n);
    }
}

void cursor_locate(unsigned int row, unsigned int column) {
    printf(ANSI_LOCATE, row, column);
}

void cursor_save(void) {
    printf(ANSI_SAVE_CURSOR);
}

void cursor_restore(void) {
    printf(ANSI_RESTORE_CURSOR);
}

void cursor_no_color(void) {
    printf(ANSI_NOCOLOR);
}

void cursor_black(void) {
    printf(ANSI_BLACK);
}

void cursor_blue(void) {
    printf(ANSI_BLUE);
}

void cursor_green(void) {
    printf(ANSI_GREEN);
}

void cursor_gold(void) {
    printf(ANSI_GOLD);
}

void cursor_gray(void) {
    printf(ANSI_GRAY);
}

void cursor_cyan(void) {
    printf(ANSI_CYAN);
}

void cursor_red(void) {
    printf(ANSI_RED);
}

void cursor_white(void) {
    printf(ANSI_WHITE);
}

void cursor_rgb(unsigned int red, unsigned int green, unsigned int blue) {
    assert(red < 256 && green < 256 && blue < 256);
    printf(ANSI_RGB, red, green, blue);
}

void cursor_black_bg(void) {
    printf(ANSI_BLACK_BG);
}

void cursor_blue_bg(void) {
    printf(ANSI_BLUE_BG);
}

void cursor_green_bg(void) {
    printf(ANSI_GREEN_BG);
}

void cursor_gold_bg(void) {
    printf(ANSI_GOLD_BG);
}

void cursor_gray_bg(void) {
    printf(ANSI_GRAY_BG);
}

void cursor_cyan_bg(void) {
    printf(ANSI_CYAN_BG);
}

void cursor_red_bg(void) {
    printf(ANSI_RED_BG);
}

void cursor_rgb_bg(unsigned int red, unsigned int green, unsigned int blue) {
    assert(red < 256 && green < 256 && blue < 256);
    printf(ANSI_RGB_BG, red, green, blue);
}

void cursor_cls(void) {
    printf(ANSI_CLS);
}

