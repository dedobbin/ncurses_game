#pragma once
#include <string>

struct Entity 
{
    Entity(std::string name, int x, int y, bool isPlayer=false);
    void tick();
    const std::string name;
    int x, y;
    bool isPlayer=false;
};