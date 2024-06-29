#include "Player.h"

Player::Player(int x, int y) 
{
    level = 1;
    hitPoints = 100;
    currentHitPoints = 100;
    strength = 10;
    currentStrength = 10;
    gold = 0;
    armor = 10;
    experience = 10;
    currentExperience = 0;
    posX = x;
    posY = y;
}

void Player::Move(int x, int y)
{
    this->posY += y;
    this->posX += x;
}