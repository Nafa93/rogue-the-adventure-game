#pragma once
#include <memory>
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity
{
public:
    Enemy(int x, int y, int hp, int chp, int str, int arm, int lvl, char spr, std::string name)
        : Entity(x, y, hp, chp, str, arm, lvl, spr, name) {}
    void MoveOrAttack(std::shared_ptr<Player>& player);
    bool CheckIfPlayerIsNear(int x, int y);
};

