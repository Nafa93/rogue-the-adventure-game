#include <cmath>
#include <vector>
#include "Enemy.h"
#include "MapManager.h"

using namespace std;

void Enemy::MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int playerX, int playerY, MapManager* mapManager)
{
	int normalizedDirectionValue; // 1 or -1
	bool playerIsNear = CheckIfPlayerIsNear(playerX, playerY);

	if (playerIsNear) {
        if (playerX != posX) {
            normalizedDirectionValue = abs(posX - playerX) / (-1 * (posX - playerX));
            char nextTile = mapManager->GetNextPosition(posX, posY, normalizedDirectionValue, 0);
            if (nextTile == '.') {
                Move(normalizedDirectionValue, 0);
            }
            else if (nextTile == '0') {
                for (auto& entity : entities) {
                    if (entity->GetPosX() == posX + normalizedDirectionValue && entity->GetPosY() == posY) {
                        if (entity->GetSprite() == '0') {
                            Attack(*entity);
                            break;
                        }
                    }
                }
            }
        }
        else if (playerY != posY) {
            normalizedDirectionValue = abs(posY - playerY) / (-1 * (posY - playerY));
            char nextTile = mapManager->GetNextPosition(posX, posY, 0, normalizedDirectionValue);
            if (nextTile == '.') {
                Move(0, normalizedDirectionValue);
            }
            else if (nextTile == '0') {
                for (auto& entity : entities) {
                    if (entity->GetPosX() == posX && entity->GetPosY() == posY + normalizedDirectionValue) {
                        if (entity->GetSprite() == '0') {
                            Attack(*entity);
                            break;
                        }
                    }
                }
            }
        }
	}
}

bool Enemy::CheckIfPlayerIsNear(int playerPosX, int playerPosY)
{
	const int SENSE_AREA_DIAMETER = 3;

	return abs(playerPosX - posX) <= SENSE_AREA_DIAMETER && abs(playerPosY - posY) <= SENSE_AREA_DIAMETER;
}

shared_ptr<Enemy> Enemy::snake(int x, int y)
{
    return make_shared<Enemy>(x, y, 10, 10, 1, 0, 1, 'S', "Snake");
}

shared_ptr<Enemy> Enemy::troll(int x, int y)
{
    return make_shared<Enemy>(x, y, 20, 10, 2, 2, 1, 'T', "Troll");
}

shared_ptr<Enemy> Enemy::zombie(int x, int y)
{
    return make_shared<Enemy>(x, y, 10, 10, 3, 1, 1, 'Z', "Zombie");
}