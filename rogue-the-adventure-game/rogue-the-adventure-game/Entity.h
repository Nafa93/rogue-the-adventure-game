#pragma once
#include <string>
#include <vector>
#include <memory>

class MapManager;

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

    virtual void MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager) = 0;

    char GetSprite() { return sprite; }
    int GetPosX() { return posX; }
    int GetPosY() { return posY; }

    void Attack(Entity& target)
    {
        int damage = strength - target.armor;
        if (damage < 0) damage = 0;
        target.ReceiveDamage(damage);
    }

    void ReceiveDamage(int damage)
    {
        currentHitPoints -= damage;
        if (currentHitPoints < 0) currentHitPoints = 0;
    }

    bool IsAlive() const { return currentHitPoints > 0; }
};