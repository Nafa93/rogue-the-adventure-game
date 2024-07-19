#include "Player.h"
#include "MapManager.h"
#include "Enemy.h"
#include "Consumable.h"

using namespace std;

void Player::MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager)
{
    char character = mapManager->GetNextPosition(posX, posY, x, y);
    bool entityFound = false;

    for (auto& entity : entities) {
        for (auto& entity : entities) {
            if (auto enemy = dynamic_pointer_cast<Enemy>(entity)) {
                if (enemy->GetPosX() == posX + x && enemy->GetPosY() == posY + y) {
                    if (enemy->GetSprite() != '.') {
                        Attack(*enemy);
                        break;
                    }
                }
            }

            if (auto consumable = dynamic_pointer_cast<Consumable>(entity)) {
                consumable->consume(this);
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