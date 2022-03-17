#include <iostream>
#include "screen.h"

int main (int argc, char *argv[])
{
    auto windows = ncurses_init(); 
    do {
        ncurses_game_render(windows.get());
        debug_print(windows.get(), "Hello World!");
    } while (ncurses_get_input());
    ncurses_quit();
    return 0;
}