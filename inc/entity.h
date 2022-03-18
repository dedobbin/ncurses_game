#pragma once
#include <string>
#include <memory>
struct Room; //forward declaration because circular dependency

struct Entity 
{
    Entity(std::string name, int x, int y, bool isPlayer=true);
    Entity(std::string name, int x, int y, void (*behaviorCallback)(std::shared_ptr<Entity>, Room*));
    const std::string name;
    int x, y;
    bool isPlayer=false;
    void (*behaviorCallback)(std::shared_ptr<Entity> self, Room* room);
};