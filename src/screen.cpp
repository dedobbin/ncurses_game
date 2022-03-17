#include "screen.h"
#include <memory>

void window_deleter(WINDOW *win)
{
    std::cout << "window deleted" << std::endl;
    delwin(win);
}

Windows::Windows(WINDOW* game)
: game(game, &window_deleter)
{}

std::unique_ptr<Windows> ncurses_init()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    //todo: define
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);


    auto windows = std::make_unique<Windows>(newwin(30,30,0,0));
    return windows;
}


void ncurses_quit()
{
    //TODO: could be done using RAII
    endwin();
}

/**
 * Returns true if didn't quit 
 */
bool ncurses_get_input()
{
    int ch = getch();
    switch(ch) {
        case KEY_UP:
            break;
        case KEY_DOWN:
            break;
        case KEY_LEFT:
            break;
        case KEY_RIGHT:
            break;
        case KEY_BACKSPACE:
            break;
        case KEY_DC:
            break;
        case KEY_HOME:
            break;
        case KEY_END:
            break;
        case KEY_PPAGE:
            break;
        case KEY_NPAGE:
            break;
        case KEY_F(1):
            break;
        case KEY_F(2):
            break;
        case KEY_F(3):
            break;
        case KEY_F(4):
            break;
        case KEY_F(5):
            break;
        case KEY_F(6):
            break;
        case KEY_F(7):  
            break;
        case 'q': case 'Q':
            return false;
    }
    return true;
}

void ncurses_render(Windows* w)
{
    refresh();
    wrefresh(w->game.get());
}