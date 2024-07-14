#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
    int gold;
    int experience;
    int currentExperience;

    Player(int x, int y)
        : Entity(x, y, 100, 100, 10, 0, 1, '0', "Player"), gold(0), experience(0), currentExperience(0) {};
};

