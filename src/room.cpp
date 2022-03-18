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

void Room::moveEntity(std::shared_ptr<Entity> e, int x, int y)
{
    if (x < 0 || x >= w || y < 0 || y >= h) return;
    //todo: check for walls
    auto collider = getEntity(x, y);
    if (!collider) {
        e->x = x;
        e->y = y;
    } else {
        //todo: effects etc
    }
}