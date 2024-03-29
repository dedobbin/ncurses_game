#pragma once
#include <vector>
#include <memory>
#include "entity.h"
#include "common.h"

struct Room 
{
    Room(int w, int h);
    void tick();
    void moveEntity(std::shared_ptr<Entity> e, int x, int y);
    void moveEntity(std::shared_ptr<Entity> e, Dir dir);
    std::shared_ptr<Entity> getEntity(int x, int y);
    std::vector<std::shared_ptr<Entity>> aliveEntities();
    void entityLook(std::shared_ptr<Entity> e, int x2, int y2,
        std::vector<std::shared_ptr<Entity>> &output);
    bool hasWall(int x, int y);
    const int w;
    const int h;
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Wall>> walls;
    std::shared_ptr<Entity> getPlayer();
    std::pair<int, int> getRandomEmptyPos();
};