#pragma once
#include <memory>
#include <ncurses.h>
#include <iostream>
#include "room.h"

void window_deleter(WINDOW *win);

typedef std::unique_ptr<WINDOW, decltype(&window_deleter)> window_ptr;

struct Windows
{
    Windows(WINDOW* game, WINDOW* stats, WINDOW* debug);
    window_ptr game;
    window_ptr stats;
    window_ptr debug;
};

struct Sys
{
    public:
        Sys();
        ~Sys();
        bool ncurses_input(Room* room);
        void ncurses_game_render(Room* r);
        void debug_print(std::string str);
    private:
        void ncurses_init();
        std::unique_ptr<Windows> windows;
};