#include <iostream>
#include "screen.h"

int main (int argc, char *argv[])
{
    ncurses_init(); 
    while (ncurses_get_input()) {
    }
    ncurses_quit();
    return 0;
}