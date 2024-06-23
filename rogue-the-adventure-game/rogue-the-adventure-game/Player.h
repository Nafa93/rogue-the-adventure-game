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

    void move(int x, int y);

    int getPosX() { return this->posX; }
    int getPosY() { return this->posY; }
};

