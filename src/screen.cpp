#include "screen.h"
#include <memory>

void window_deleter(WINDOW *win)
{
    //std::cout << "window deleted" << std::endl;
    delwin(win);
}

Windows::Windows(WINDOW* game, WINDOW* stats, WINDOW* debug)
: game(game, &window_deleter), stats(stats, &window_deleter), debug(debug, &window_deleter)
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


    auto windows = std::make_unique<Windows>(
        newwin(30,30,0,0),
        newwin(30,30,30,0),
        newwin(30,30,0,30)
    );
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

void ncurses_game_render(Windows* w, Room* r)
{
    //todo: check if fits in screen
    for (int y = 0; y < r->h; y++) {
        for (int x = 0; x < r->w; x++) {
            mvwaddch(w->game.get(), y, x, '.');
        }
    }

    for(auto &e: r->entities){
        if (e->isPlayer) {
            wattron(w->game.get(), COLOR_PAIR(2));
            mvwaddch(w->game.get(), e->y, e->x, '@');
            wattroff(w->game.get(), COLOR_PAIR(7));
        } else {
            wattron(w->game.get(), COLOR_PAIR(1));
            mvwaddch(w->game.get(), e->y, e->x, 'o');
            wattroff(w->game.get(), COLOR_PAIR(1));
        }
    }

    refresh();
    wrefresh(w->game.get());
}

void debug_print(Windows* w, std::string str)
{
    str += '\n';
    wprintw(w->debug.get(), str.c_str());
    wrefresh(w->debug.get());
}