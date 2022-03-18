#pragma once
#include <string>
#include <memory>
struct Room; //forward declaration because circular dependency

struct Entity 
{
    Entity(std::string name, int x, int y, bool isPlayer=true, bool isSolid=true);
    Entity(std::string name, int x, int y, void (*behaviorCallback)(std::shared_ptr<Entity>, Room*), bool isSolid=true);
    const std::string name;
    int x, y;
    bool isPlayer=false;
    bool isSolid=true;
    void (*behaviorCallback)(std::shared_ptr<Entity> self, Room* room);
};

struct Wall
{
    int x,y;
};