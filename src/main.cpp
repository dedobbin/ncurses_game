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
    //todo: probably more efficient to find entities in box around self,
    // then check if there is a wall between entity and self, if not add to spotted
    auto tl = std::make_pair(self->x - 2, self->y - 2);
    auto tr = std::make_pair(self->x + 2, self->y - 2);
    auto bl = std::make_pair(self->x - 2, self->y + 2);
    auto br = std::make_pair(self->x + 2, self->y + 2);

    std::vector<std::shared_ptr<Entity>> spotted = {};
    for (int x = tl.first; x < tr.first; x++){
        int y = tl.second;
        room->entityLook(self, x, y, spotted);
    }

    for (int y = tr.second; y < br.second; y++){
        int x = tr.first;
        room->entityLook(self, x, y, spotted);
    }

    for (int x = br.first; x > bl.first; x--){
        int y = br.second;
        room->entityLook(self, x, y, spotted);

    }

    for (int y = bl.second; y > tl.second; y--){
        int x = bl.first;
        room->entityLook(self, x, y, spotted);
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