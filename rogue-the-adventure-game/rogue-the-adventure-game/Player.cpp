#include "Player.h"
#include "MapManager.h"

void Player::MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager)
{
    char character = mapManager->GetNextPosition(posX, posY, x, y);

    switch (character) {
    case '.':
        Move(x, y);
        break;
    default:
        for (auto& entity : entities) {
            if (entity->GetPosX() == posX + x && entity->GetPosY() == posY + y) {
                if (entity->GetSprite() != '.') {
                    Attack(*entity);
                    break;
                }
            }
        }
        break;
    }
}