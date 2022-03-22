#include "combat.h"

#include "entity.h"


Combat::Combat(Entity* a, Entity* b)
{
    combatants.push_back(a);
    combatants.push_back(b);
}