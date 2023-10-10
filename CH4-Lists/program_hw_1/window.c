#include "includes.h"
#include "window.h"


const char *strTERMINAL = " TERMINAL ";
const char *strMENU = " MENU ";
const char *strSTORAGE = " STORAGE ";

WINDOW *winTERMINAL, *winMENU, *winSTORAGE;

// ==============================================================================================================================
void initialize_color() {
    // COLOR_BLACK
    // COLOR_RED
    // COLOR_GREEN
    // COLOR_YELLOW
    // COLOR_BLUE
    // COLOR_MAGENTA
    // COLOR_CYAN
    // COLOR_WHITE
	start_color();
	init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_RED);
    // use_default_colors();
}
// ==============================================================================================================================
void initialize_ncurses() {
    setlocale(LC_ALL, ""); // setlocale(LC_ALL, "en_US.UTF-8");

    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    if(has_colors() == FALSE) {	
        clear();
		printw("Your terminal does not support color\nPress any key to exit...\n");
        getch();
        endwin();
        exit(0);
	}
    initialize_color();
}
// ==============================================================================================================================
void initialize_window() {
    winTERMINAL   = newwin(WINDOW_TERMINAL_HEIGHT,   WINDOW_TERMINAL_WIDTH,   WINDOW_TERMINAL_STARTY,   WINDOW_TERMINAL_STARTX);
    winMENU       = newwin(WINDOW_MENU_HEIGHT,       WINDOW_MENU_WIDTH,       WINDOW_MENU_STARTY,       WINDOW_MENU_STARTX);
    winSTORAGE    = newwin(WINDOW_STORAGE_HEIGHT,    WINDOW_STORAGE_WIDTH,    WINDOW_STORAGE_STARTY,    WINDOW_STORAGE_STARTX);
    
    refresh();

    box(winTERMINAL   , 0, 0);
    box(winMENU       , 0, 0);
    box(winSTORAGE    , 0, 0);
    
    mvwprintw(winTERMINAL,   0, (WINDOW_TERMINAL_WIDTH   - strlen(strTERMINAL))   / 2 + 1, "%s", strTERMINAL);
    mvwprintw(winMENU,       0, (WINDOW_MENU_WIDTH       - strlen(strMENU))       / 2 + 1, "%s", strMENU);
    mvwprintw(winSTORAGE,    0, (WINDOW_STORAGE_WIDTH    - strlen(strSTORAGE))    / 2 + 1, "%s", strSTORAGE);

    wrefresh(winTERMINAL);
    wrefresh(winMENU);
    wrefresh(winSTORAGE);

    refresh();
}
// ==============================================================================================================================
// ==============================================================================================================================
/* Usage
    const char *tempMessage[1] = {"text"};
    print_message(tempMessage, 1, 0);
*/
void print_message(char **ptr_strMessage, int32_t intLengthOfStringArray, int32_t WhetherToClean) {
    wattron(winTERMINAL, A_REVERSE);
    for (int32_t i = 0; i < intLengthOfStringArray; i++) {
        mvwprintw(winTERMINAL, i + 2, 2, "%s" , ptr_strMessage[i]);
    }
    wattroff(winTERMINAL, A_REVERSE);
    if (WhetherToClean) {
        clean_message(0);
    }
    else {
        wrefresh(winTERMINAL);
    }
}
// ==============================================================================================================================
void clean_message(int32_t WhetherDirectlyClean) {
    if (!WhetherDirectlyClean) {
        int32_t yEnd, xEnd;
        getmaxyx(winTERMINAL, yEnd, xEnd);
        mvwprintw(winTERMINAL, yEnd - 2, 2, "Press q to quit and other keys to continue...");

        wrefresh(winTERMINAL);

        if (getch() == 'q') {
            endwin();
            exit(0);
        }

    } 
    
    wclear(winTERMINAL);
    box(winTERMINAL, 0, 0);
    mvwprintw(winTERMINAL, 0, (WINDOW_TERMINAL_WIDTH - strlen(strTERMINAL)) / 2 + 1, "%s", strTERMINAL);

    wrefresh(winTERMINAL);
}
// ==============================================================================================================================
int32_t menu_select() {
    keypad(winMENU, TRUE);

    int32_t intHightLight = 0;
    int32_t intPlayerChoice = 0;

    int32_t intChoiceSize = 9;
    char *ptr_strChoice[9] = {\
    "1. Input New Polynomial",\
    "2. Display Specfic Coefficient",\
    "3. Add a term to the polynomial",\
    "4. Remove a specified exponent",\
    "5. Add two polynomials",\
    "6. Minus two polynomials",\
    "7. Multiply two polynomials",\
    "8. Divide two polynomials",\
    "9. Quit"};


    while(1) {
        for (int32_t i = 0; i < intChoiceSize; ++i) {
            if (i == intHightLight) {
                wattron(winMENU, A_REVERSE);
                mvwprintw(winMENU, i + 1, 2, "%s <————", ptr_strChoice[i]);
            }
            else {
                mvwprintw(winMENU, i + 1, 2, "%s      ", ptr_strChoice[i]);
            }
            wattroff(winMENU, A_REVERSE);
        }
        intPlayerChoice = wgetch(winMENU);

        switch (intPlayerChoice)
        {
        case KEY_UP:
            --intHightLight;
            if (intHightLight == -1) {
                intHightLight = intChoiceSize - 1;
            }
            break;
        case KEY_DOWN:
            ++intHightLight;
            if (intHightLight == intChoiceSize) {
                intHightLight = 0;
            }
        default:
            break;
        }
        if (intPlayerChoice == 10) {
            break;
        }
    }

    clean_menu();
    return intHightLight;
}
// ==============================================================================================================================
void clean_menu() {
    wclear(winMENU);
    box(winMENU, 0, 0);
    mvwprintw(winMENU, 0, (WINDOW_MENU_WIDTH - strlen(strMENU)) / 2 + 1, "%s", strMENU);

    wrefresh(winMENU);
}