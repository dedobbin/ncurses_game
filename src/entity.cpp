#include <cassert>
#include "entity.h"
#include "sys.h"

Entity::Entity(std::string name, int x, int y, bool isSolid)
: name(name), x(x), y(y), isSolid(isSolid), stats(nullptr)
{}

Entity::Entity(std::string name, int x, int y, bool isSolid, Stats* stats)
: name(name), x(x), y(y), isSolid(isSolid), stats(std::unique_ptr<Stats>(stats))
{}

//todo: pass in spell or weapon or whatever using templates
void Entity::attack(Entity* other, Sys* sys)
{
    assert(stats);
    assert(other->stats);
    other->stats->hp -= stats->power;
    sys->info(name + " hits " + other->name);
}

std::shared_ptr<Entity> EntityBuilder::player(std::string name, int x, int y,
        void (*effectCallback)(std::shared_ptr<Entity>, std::shared_ptr<Entity>, Room*)
    )
{
    auto player = std::make_shared<Entity>(name, x, y, true, new Stats{100, 10});
    player->effectCallback = effectCallback;
    player->isPlayer = true;
    return player;
}

std::shared_ptr<Entity> EntityBuilder::enemy(std::string name, int x, int y, bool isSolid,
    Stats* stats,
    void (*behaviorCallback)(std::shared_ptr<Entity>, Room*),
    void (*effectCallback)(std::shared_ptr<Entity>, std::shared_ptr<Entity>, Room*)
){
    auto enemy = std::make_shared<Entity>(name, x, y, isSolid, stats);
    enemy->behaviorCallback = behaviorCallback;
    enemy->effectCallback = effectCallback;
    return enemy;
}