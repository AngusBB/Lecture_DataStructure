#pragma once

#include "includes.h"

# define WINDOW_TERMINAL_HEIGHT 15
# define WINDOW_TERMINAL_WIDTH  130
# define WINDOW_TERMINAL_STARTX 0
# define WINDOW_TERMINAL_STARTY 0

# define WINDOW_MENU_HEIGHT 15
# define WINDOW_MENU_WIDTH  40
# define WINDOW_MENU_STARTX (WINDOW_TERMINAL_WIDTH)
# define WINDOW_MENU_STARTY 0

# define WINDOW_STORAGE_HEIGHT 15
# define WINDOW_STORAGE_WIDTH  170
# define WINDOW_STORAGE_STARTX 0
# define WINDOW_STORAGE_STARTY (WINDOW_MENU_HEIGHT)

extern WINDOW *winTERMINAL, *winMENU, *winSTORAGE;

void initialize_color();
void initialize_ncurses();
void initialize_window();

void print_message(char **ptr_strMessage, int32_t intLengthOfStringArray, int32_t WetherToClean);
void clean_message(int32_t WetherDirectlyClean);

int32_t menu_select();
void clean_menu();