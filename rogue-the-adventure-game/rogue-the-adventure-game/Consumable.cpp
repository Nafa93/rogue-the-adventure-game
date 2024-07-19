#include "Consumable.h"
#include "Player.h"
#include <vector>

using namespace std;

void Consumable::MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager, MessageManager* messageManager)
{
    return;
}

shared_ptr<Consumable> Consumable::potion(int x, int y)
{
    auto consume = [](Player* player) {
        player->currentHitPoints = min(player->hitPoints, player->currentHitPoints + 50);
    };

    return make_shared<Consumable>(x, y, 1, 1, 0, 0, 0, 'P', "Potion", consume);
}

shared_ptr<Consumable> Consumable::armor(int x, int y)
{
    auto consume = [](Player* player) {
        player->armor += 10;
    };
    return make_shared<Consumable>(x, y, 1, 1, 0, 0, 0, 'D', "Defense boost", consume);
}

shared_ptr<Consumable> Consumable::strength(int x, int y)
{
    auto consume = [](Player* player) {
        player->strength += 10;
    };
    return make_shared<Consumable>(x, y, 1, 1, 0, 0, 0, 'A', "Attack boost", consume);
}