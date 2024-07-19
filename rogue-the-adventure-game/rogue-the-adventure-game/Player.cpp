#include "Player.h"
#include "MapManager.h"
#include "Enemy.h"
#include "Consumable.h"

void Player::MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager, MessageManager* messageManager)
{
    char character = mapManager->GetNextPosition(posX, posY, x, y);
    bool entityFound = false;

    for (auto& entity : entities) {
        if (auto enemy = dynamic_pointer_cast<Enemy>(entity)) {
            if (entity->GetPosX() == posX + x && entity->GetPosY() == posY + y && entity->IsAlive()) {
                entityFound = true;
                Attack(*entity, messageManager);

                break;
            }
        }

        if (auto consumable = dynamic_pointer_cast<Consumable>(entity)) {
            if (entity->GetPosX() == posX + x && entity->GetPosY() == posY + y) {
                consumable->currentHitPoints = 0;
                consumable->consume(this);
                messageManager->AddMessage("Se ha utilizado " + consumable->GetName());
                break;
            }
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
