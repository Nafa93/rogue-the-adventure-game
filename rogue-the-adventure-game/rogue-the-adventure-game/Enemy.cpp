#include <cmath>
#include "Enemy.h"
#include "MapManager.h"

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