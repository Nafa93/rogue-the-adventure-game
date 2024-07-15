#include "Enemy.h"
#include <cmath>

void Enemy::MoveOrAttack(std::shared_ptr<Player>& player) 
{
	bool playerIsNear = CheckIfPlayerIsNear(player->GetPosX(), player->GetPosY());

	if (playerIsNear) {
		if (player->GetPosX() != posX) posX += abs(posX - player->GetPosX()) / (-1 * (posX - player->GetPosX()));
		else if (player->GetPosY() != posY) posY += abs(posY - player->GetPosY()) / (-1 * (posY - player->GetPosY()));
	}
}

bool Enemy::CheckIfPlayerIsNear(int playerPosX, int playerPosY)
{
	const int SENSE_AREA_DIAMETER = 3;

	return abs(playerPosX - posX) <= 3 && abs(playerPosY - posY) <= 3;
}