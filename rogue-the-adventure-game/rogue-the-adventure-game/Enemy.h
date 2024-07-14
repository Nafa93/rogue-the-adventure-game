#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy(int x, int y, int hp, int chp, int str, int arm, int lvl, char spr, std::string name)
        : Entity(x, y, hp, chp, str, arm, lvl, spr, name) {}
};

