#pragma once
#include <memory>
#include <ncurses.h>
#include <iostream>

void window_deleter(WINDOW *win);

struct Windows
{
    Windows(WINDOW* game);
    std::unique_ptr<WINDOW, decltype(&window_deleter)> game;
};

std::unique_ptr<Windows>  ncurses_init();
void ncurses_quit();
bool ncurses_get_input();
void ncurses_render(Windows* w);