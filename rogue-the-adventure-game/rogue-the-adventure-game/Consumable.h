#pragma once
#include <memory>
#include <functional>
#include "Player.h"
#include "Entity.h"

using namespace std;

class Consumable : public Entity
{
public:
	Consumable(int x, int y, int hp, int chp, int str, int arm, int lvl, char spr, std::string name, function<void(Player*)> consume)
		: Entity(x, y, hp, chp, str, arm, lvl, spr, name), consume(consume) {}
	
	void MoveOrAttack(std::vector<std::shared_ptr<Entity>>& entities, int x, int y, MapManager* mapManager) override;

	static shared_ptr<Consumable> potion(int x, int y);
	static shared_ptr<Consumable> armor(int x, int y);
	static shared_ptr<Consumable> strength(int x, int y);

	function<void(Player*)> consume;
};