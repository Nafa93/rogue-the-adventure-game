#include "Consumable.h"
#include "Player.h"
#include <vector>

using namespace std;

void Consumable::MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager)
{
    return;
}

shared_ptr<Consumable> Consumable::potion(int x, int y)
{
    auto consumePotion = [](Player* player) {
        player->currentHitPoints = min(player->hitPoints, player->currentHitPoints + 50);
    };

    return make_shared<Consumable>(x, y, 50, 0, 0, 0, 0, 'P', "Potion", consumePotion);
}

//shared_ptr<Consumable> Consumable::armor(int x, int y)
//{
//    return make_shared<Consumable>(x, y, 0, 0, 0, 10, 0, 'A', "Armor boost");
//}
//
//shared_ptr<Consumable> Consumable::strength(int x, int y)
//{
//    return make_shared<Consumable>(x, y, 0, 0, 10, 0, 0, 'S', "Strength boost");
//}