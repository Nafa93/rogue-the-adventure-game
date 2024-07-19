#include "Player.h"
#include "MapManager.h"

void Player::MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager, MessageManager* messageManager)
{
    char character = mapManager->GetNextPosition(posX, posY, x, y);
    bool entityFound = false;

    for (auto& entity : entities) {
        if (entity->GetPosX() == posX + x && entity->GetPosY() == posY + y && entity->IsAlive()) {
            entityFound = true;
            Attack(*entity, messageManager);

            break;
        }
    }

    if (!entityFound) {
        switch (character) {
        case '.':
            Move(x, y);
            break;
        case '$':
            Move(x, y);
            break;
        default:
            break;
        }
    }
}
