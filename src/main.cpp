#include <iostream>
#include "screen.h"
#include "room.h"

std::unique_ptr<Room> create_room(int id)
{
    switch(id)
    {
        case 1:
            // TODO: check if this is copied? i think so? thats not efficient. maybe. who cares, its small.
            return std::make_unique<Room>(10, 10);
        case 2:{
            auto room = std::make_unique<Room>(10, 10);
            room->entities.emplace_back(new Entity("enemy_1", 3, 5));
            return room;
        }
        default:
            throw std::runtime_error("invalid room id");
    }
}

int main (int argc, char *argv[])
{
    auto windows = ncurses_init(); 
    auto room = create_room(2);
    auto player = std::make_shared<Entity>("player", 0, 0, true);
    room->entities.push_back(player);
    do {
        ncurses_game_render(windows.get(), room.get());
    } while (ncurses_input(room.get()));
    ncurses_quit();
    return 0;
}