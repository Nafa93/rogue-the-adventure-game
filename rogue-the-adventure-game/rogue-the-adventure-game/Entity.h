#pragma once
#include <string>

class Entity
{
public:
    int posX;
    int posY;
    int hitPoints;
    int currentHitPoints;
    int strength;
    int armor;
    int level;
    char sprite;
    std::string name;

    virtual ~Entity() = default;

    Entity(int x, int y, int hp, int chp, int str, int arm, int lvl, char spr, std::string name)
        : posX(x), posY(y), hitPoints(hp), currentHitPoints(chp), strength(str), armor(arm), level(lvl), sprite(spr), name(name) {}

    void Move(int x, int y)
    {
        posX += x;
        posY += y;
    }

    char GetSprite() { return sprite; }
    int GetPosX() { return posX; }
    int GetPosY() { return posY; }
};

