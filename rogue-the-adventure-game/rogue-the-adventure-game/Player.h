#pragma once
#include <memory>
#include <vector>
#include "Entity.h"

class MapManager;

class Player : public Entity
{
public:
    int gold;
    int experience;
    int currentExperience;

    void MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager) override;

    Player(int x, int y)
        : Entity(x, y, 100, 100, 10, 0, 1, '0', "Player"), gold(0), experience(0), currentExperience(0) {};
};

