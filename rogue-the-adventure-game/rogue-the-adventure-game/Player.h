#pragma once
class Player
{
public:
    int level;
    int hitPoints;
    int currentHitPoints;
    int strength;
    int currentStrength;
    int gold;
    int armor;
    int experience;
    int currentExperience;
    int posY;
    int posX;

    Player(int x, int y);

    void Move(int x, int y);

    int GetPosX() { return this->posX; }
    int GetPosY() { return this->posY; }
};

