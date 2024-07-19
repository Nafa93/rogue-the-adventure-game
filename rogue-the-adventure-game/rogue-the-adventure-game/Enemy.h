#pragma once
#include <memory>
#include <vector>
#include "Entity.h"
#include "Player.h"

using namespace std;

class Enemy : public Entity
{
public:
    Enemy(int x, int y, int hp, int chp, int str, int arm, int lvl, char spr, std::string name)
        : Entity(x, y, hp, chp, str, arm, lvl, spr, name) {}

    void MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager) override;
    bool CheckIfPlayerIsNear(int x, int y);
    static shared_ptr<Enemy> snake(int x, int y);
    static shared_ptr<Enemy> troll(int x, int y);
    static shared_ptr<Enemy> zombie(int x, int y);
};

