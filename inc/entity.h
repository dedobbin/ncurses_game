#pragma once
#include <string>
#include <memory>
#include "combat.h"
struct Room; //forward declaration because circular dependency

struct Entity 
{
    Entity(std::string name, int x, int y, bool isPlayer=true, bool isSolid=true);
    Entity(std::string name, int x, int y, 
        void (*behaviorCallback)(std::shared_ptr<Entity>, Room*), 
        void (*effectCallback)(std::shared_ptr<Entity> self, std::shared_ptr<Entity> other, Room* room),
        bool isSolid=true
    );
    const std::string name;
    int x, y;
    bool isPlayer=false;
    bool isSolid=true;
    void (*behaviorCallback)(std::shared_ptr<Entity> self, Room* room);
    void (*effectCallback)(std::shared_ptr<Entity> self, std::shared_ptr<Entity> other, Room* room);
    std::shared_ptr<Combat> combat;
};

struct Wall
{
    int x,y;
};