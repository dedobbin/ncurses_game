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

std::unique_ptr<Windows>  ncurses_init();
void ncurses_quit();
bool ncurses_input(Room* room);
void ncurses_game_render(Windows* w, Room* r);
void debug_print(Windows* w, std::string str);