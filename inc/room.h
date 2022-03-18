#pragma once
#include <vector>
#include <memory>
#include "entity.h"

struct Room 
{
    Room(int w, int h);
    void tick();
    void moveEntity(std::shared_ptr<Entity> e, int x, int y);
    std::shared_ptr<Entity> getEntity(int x, int y);
    const int w;
    const int h;
    std::vector<std::shared_ptr<Entity>> entities;
    std::shared_ptr<Entity> getPlayer();
};