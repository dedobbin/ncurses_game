#include <iostream>
#include "screen.h"
#include "room.h"

int main (int argc, char *argv[])
{
    auto windows = ncurses_init(); 
    Room room(10,10);
    do {
        ncurses_game_render(windows.get(), room);
    } while (ncurses_get_input());
    ncurses_quit();
    return 0;
}