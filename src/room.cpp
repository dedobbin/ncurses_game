#include "room.h"
#include <cassert>
#include <algorithm>

Room::Room(int w, int h)
:w(w), h(h)
{}

std::shared_ptr<Entity> Room::getPlayer()
{
    auto found = std::find_if(entities.begin(), entities.end(), [](const std::shared_ptr<Entity>& e) {
        return e->isPlayer;
    });
    assert(*found);
    return *found;
}

void Room::tick()
{
    for (auto &e: entities) {
        if (!e->behaviorCallback) continue;
        e->behaviorCallback(e, this);
    }
}

std::shared_ptr<Entity> Room::getEntity(int x, int y)
{
    auto found = std::find_if (entities.begin(), entities.end(), [x, y](const std::shared_ptr<Entity>& e) {
        return e->x == x && e->y == y;
    });

    return found != entities.end() ? *found : nullptr;
}

bool Room::hasWall(int x, int y)
{
    auto found = std::find_if (walls.begin(), walls.end(), [x, y](const std::unique_ptr<Wall>& w) {
        return w->x == x && w->y == y;
    });

    return found != walls.end();
}

void Room::moveEntity(std::shared_ptr<Entity> e, int x, int y)
{
    if (x < 0 || x >= w || y < 0 || y >= h) return;
    
    if (hasWall(x, y)) return;

    auto collider = getEntity(x, y);
    if (!collider) {
        e->x = x;
        e->y = y;
    } else {
        //todo: effects etc
    }
}

std::pair<int, int> Room::getRandomEmptyPos()
{
    int x, y;
    int tries = 100;
    do {
        x = rand() % w;
        y = rand() % h;
        tries --;
        if (tries == 0){
            throw std::runtime_error("could not find empty position");
        }
    } while (getEntity(x, y) || hasWall(x, y));
    return {x, y};
}