#include <cmath>
#include <vector>
#include "Enemy.h"
#include "MapManager.h"

using namespace std;

void Enemy::MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int playerX, int playerY, MapManager* mapManager, MessageManager* messageManager)
{
    int normalizedDirectionX = 0;
    int normalizedDirectionY = 0;
    int nextPosX = posX, nextPosY = posY;
	bool playerIsNear = CheckIfPlayerIsNear(playerX, playerY);
    bool playerNextTile = false;

	if (playerIsNear) {
        if (playerX != posX) {
            normalizedDirectionX = (playerX - posX) / std::abs(playerX - posX);
        }
        else if (playerY != posY) {
            normalizedDirectionY = (playerY - posY) / std::abs(playerY - posY);
        }

        nextPosX = posX + normalizedDirectionX;
        nextPosY = posY + normalizedDirectionY;

        if (nextPosX == playerX && nextPosY == playerY) {
            playerNextTile = true;
            for (auto& entity : entities) {
                if (entity->GetSprite() == '0') {
                    Attack(*entity, messageManager);
                    break;
                }
            }
        }
	}

    if (!playerNextTile) {
        char nextTile = mapManager->GetNextPosition(posX, posY, normalizedDirectionX, normalizedDirectionY);

        if (nextTile == '.' || nextTile == '$$') {
            Move(normalizedDirectionX, normalizedDirectionY);
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