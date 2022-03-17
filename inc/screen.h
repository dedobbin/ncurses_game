#pragma once
#include <memory>
#include <ncurses.h>
#include <iostream>

void window_deleter(WINDOW *win);

struct Windows
{
    Windows(WINDOW* game, WINDOW* stats, WINDOW* debug);
    std::unique_ptr<WINDOW, decltype(&window_deleter)> game;
    std::unique_ptr<WINDOW, decltype(&window_deleter)> stats;
    std::unique_ptr<WINDOW, decltype(&window_deleter)> debug;
};

std::unique_ptr<Windows>  ncurses_init();
void ncurses_quit();
bool ncurses_get_input();
void ncurses_game_render(Windows* w);
void debug_print(Windows* w, std::string str);