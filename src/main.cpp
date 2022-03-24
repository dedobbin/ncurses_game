#include <iostream>
#include <cassert>
#include <algorithm>
#include "sys.h"
#include "room.h"

Sys sys;

int get_slope(int x1, int y1, int x2, int y2)
{
    if (x1 == x2)
        return 0;

    return (y1 - y2) / (x1 - x2);
}

std::vector<std::pair<int, int>> get_points_between(int x1, int y1, int x2, int y2)
{
    //bresenhamsLineGeneration
    std::vector<std::pair<int, int>> points;
    bool issteep = (abs(y2 - y1) > abs(x2 - x1));
    if (issteep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }
    bool rev = false;
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
        rev = true;
    }
    int deltax = x2 - x1;
    int deltay = abs(y2 - y1);
    int error  = int(deltax / 2);
    int y      = y1;
    int ystep;
    if (y1 < y2) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (int x = x1; x < x2 + 1; ++x) {
        if (issteep) {
            std::pair<int, int> pt = std::make_pair(y, x);
            points.emplace_back(pt);
        } else {
            std::pair<int, int> pt = std::make_pair(x, y);
            points.emplace_back(pt);
        }

        error -= deltay;
        if (error < 0) {
            y += ystep;
            error += deltax;
        }
    }
    // Reverse the list if the coordinates were reversed
    if (rev) {
        std::reverse(points.begin(), points.end());
    }
    
    return points;
}

void enemy_behavior_rand(std::shared_ptr<Entity> self, Room* room)
{
    switch(rand() % 4){
        case 0:
            room->moveEntity(self, self->x + 1, self->y);
            break;
        case 1:
            room->moveEntity(self, self->x - 1, self->y);
            break;
        case 2:
            room->moveEntity(self, self->x, self->y + 1);
            break;
        case 3:
            room->moveEntity(self, self->x, self->y - 1);
            break;
    }
}

void enemy_behavior(std::shared_ptr<Entity> self, Room* room)
{
    auto tl = std::make_pair(self->x - 2, self->y - 2);
    auto tr = std::make_pair(self->x + 2, self->y - 2);
    auto bl = std::make_pair(self->x - 2, self->y + 2);
    auto br = std::make_pair(self->x + 2, self->y + 2);

    std::vector<std::shared_ptr<Entity>> spotted;
    for (int x = tl.first; x < tr.first; x++){
        int y = tl.second;
        for (auto pt : get_points_between(self->x, self->y, x, y)){
            if (room->hasWall(pt.first, pt.second)){
                break;
            }
            auto spottedEntity = room->getEntity(pt.first, pt.second);
            if (spottedEntity && spottedEntity != self){
                spotted.push_back(spottedEntity);
            }
        }
    }

    for (int y = tr.second; y < br.second; y++){
        int x = tr.first;
        for (auto pt : get_points_between(self->x, self->y, x, y)){
            if (room->hasWall(pt.first, pt.second)){
                break;
            }
            auto spottedEntity = room->getEntity(pt.first, pt.second);
            if (spottedEntity && spottedEntity != self){
                spotted.push_back(spottedEntity);
            }
        }
    }

    for (int x = br.first; x > bl.first; x--){
        int y = br.second;
        for (auto pt : get_points_between(self->x, self->y, x, y)){
            if (room->hasWall(pt.first, pt.second)){
                break;
            }
            auto spottedEntity = room->getEntity(pt.first, pt.second);
            if (spottedEntity && spottedEntity != self){
                spotted.push_back(spottedEntity);
            }
        }
    }

    for (int y = bl.second; y > tl.second; y--){
        int x = bl.first;
        for (auto pt : get_points_between(self->x, self->y, x, y)){
            if (room->hasWall(pt.first, pt.second)){
                break;
            }
            auto spottedEntity = room->getEntity(pt.first, pt.second);
            if (spottedEntity && spottedEntity != self){
                spotted.push_back(spottedEntity);
            }
        }
    }

    if (find_if(spotted.begin(), spotted.end(), [](std::shared_ptr<Entity> e){
        return e->isPlayer;
    }) != spotted.end()){
        sys.info("Player spotted");
    }
}


void enemy_effect(std::shared_ptr<Entity> self, std::shared_ptr<Entity> other, Room* room)
{
    if (other->isPlayer) {
        assert(other->stats);
        self->attack(other.get(), &sys);
    }
}

void player_effect(std::shared_ptr<Entity> self, std::shared_ptr<Entity> other, Room* room)
{
    if (!other->stats) return;
    self->attack(other.get(), &sys);
}

std::unique_ptr<Room> create_room(int id)
{
    switch(id)
    {
        case 1:
            // TODO: check if this is copied? i think so? thats not efficient. maybe. who cares, its small.
            return std::make_unique<Room>(10, 10);
        case 2:{
            auto room = std::make_unique<Room>(10, 10);
            room->entities.emplace_back(new Entity("enemy_2", 2, 2, false));
            return room;
        }
        case 3:{
            auto room = std::make_unique<Room>(10, 10);
            int n_walls = 5;
            for (int i = 0; i < n_walls; i++){
                auto pos = room->getRandomEmptyPos();
                room->walls.emplace_back(new Wall{pos.first, pos.second});
            }
            
            int n_entities = 5;
            for (int i = 0; i < n_entities; i++){
                auto pos = room->getRandomEmptyPos();
                room->entities.push_back(
                    EntityBuilder::enemy("enemy", pos.first, pos.second, true, 
                        new Stats{rand () % 20, rand () % 10},
                        enemy_behavior, enemy_effect)
                ); 
                    
            }

            return room;
        }
        case 4: {
            auto room = std::make_unique<Room>(10, 10);
            room->entities.push_back(EntityBuilder::enemy("enemy", 5, 2, true, 
                new Stats{rand () % 20, rand () % 10},
                enemy_behavior, enemy_effect));
            
            int n_walls = 20;
            for (int i = 0; i < n_walls; i++){
                auto pos = room->getRandomEmptyPos();
                room->walls.emplace_back(new Wall{pos.first, pos.second});
            }
            
            return room;
        }
        default:
            throw std::runtime_error("invalid room id");
    }
}

int main (int argc, char *argv[])
{
    auto room = create_room(4);
    auto player = EntityBuilder::player("player", 5, 5, player_effect);
    room->entities.push_back(player);
    bool keepGoing = true;
    do {
        sys.ncurses_game_render(room.get());
        room->tick();
        keepGoing = sys.ncurses_input(room.get());
    } while (keepGoing);
    return 0;
}