#include "sys.h"
#include <memory>

void window_deleter(WINDOW *win)
{
    //std::cout << "window deleted" << std::endl;
    delwin(win);
}

Windows::Windows(WINDOW* game, WINDOW* stats, WINDOW* info)
: game(game, &window_deleter), stats(stats, &window_deleter), info(info, &window_deleter)
{}

Sys::Sys()
{
    ncurses_init();
}

Sys::~Sys()
{
    endwin();
}


void Sys::ncurses_init()
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

    windows = std::make_unique<Windows>(
        newwin(30,30,0,0),
        newwin(30,30,30,0),
        newwin(30,30,0,30)
    );
}

/**
 * Returns true if didn't quit 
 */
bool Sys::ncurses_input(Room * room)
{
    auto player = room->getPlayer();
    int ch = getch();
    switch(ch) {
        case KEY_UP:
            room->moveEntity(player, player->x, player->y - 1);
            break;
        case KEY_DOWN:
            room->moveEntity(player, player->x, player->y + 1);
            break;
        case KEY_LEFT:
            room->moveEntity(player, player->x - 1, player->y);
            break;
        case KEY_RIGHT:
            room->moveEntity(player, player->x + 1, player->y);
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

void Sys::ncurses_game_render(Room* r)
{
    auto game_window = windows->game.get();
    //todo: check if fits in screen
    for (int y = 0; y < r->h; y++) {
        for (int x = 0; x < r->w; x++) {
            mvwaddch(game_window, y, x, '.');
        }
    }

    for (auto& wall : r->walls){
        mvwaddch(game_window, wall->y, wall->x, '#');
    }

    for(auto &e: r->entities){
        if (e->isPlayer) {
            wattron(game_window, COLOR_PAIR(2));
            mvwaddch(game_window, e->y, e->x, '@');
            wattroff(game_window, COLOR_PAIR(7));
        } else {
            wattron(game_window, COLOR_PAIR(1));
            mvwaddch(game_window, e->y, e->x, 'o');
            wattroff(game_window, COLOR_PAIR(1));
        }
    }

    refresh();
    wrefresh(game_window);
}

void Sys::info(std::string str)
{
    str += '\n';
    wprintw(windows->info.get(), str.c_str());
    wrefresh(windows->info.get());
}