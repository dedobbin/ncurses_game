#include <iostream>
#include "sys.h"
#include "room.h"

Sys sys;

void enemy_behavior(std::shared_ptr<Entity> self, Room* room)
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

void enemy_effect(std::shared_ptr<Entity> self, std::shared_ptr<Entity> other, Room* room)
{
    if (other->isPlayer) {
        sys.info("enemy touches player");
    }
}

void player_effect(std::shared_ptr<Entity> self, std::shared_ptr<Entity> other, Room* room)
{
    sys.info("player touches enemy");

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
            room->entities.push_back(EntityBuilder::enemy("enemy", 3, 5, true, enemy_behavior, enemy_effect));
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
                    EntityBuilder::enemy("enemy", pos.first, pos.second, true, enemy_behavior, enemy_effect)
                ); 
                    
            }

            return room;
        }
        default:
            throw std::runtime_error("invalid room id");
    }
}

int main (int argc, char *argv[])
{
    auto room = create_room(3);
    auto player = EntityBuilder::player("player", 5, 5, player_effect);
    room->entities.push_back(player);
    do {
        sys.ncurses_game_render(room.get());
        room->tick();
    } while (sys.ncurses_input(room.get()));
    return 0;
}