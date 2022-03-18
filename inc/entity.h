#pragma once
#include <string>

struct Room; //forward declaration because circular dependency

struct Entity 
{
    Entity(std::string name, int x, int y, bool isPlayer=true);
    Entity(std::string name, int x, int y, void (*behaviorCallback)(Entity*, Room*));
    const std::string name;
    int x, y;
    bool isPlayer=false;
    void (*behaviorCallback)(Entity* self, Room* room);
};