#pragma once

#include <vector>

struct Entity;

struct Combat
{
    Combat(Entity* a, Entity* b);
    std::vector<Entity*> combatants;//can't use smart ptr because circular
};