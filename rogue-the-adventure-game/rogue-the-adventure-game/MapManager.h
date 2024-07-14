#pragma once
#include "Player.h"
#include "ConsoleHelper.h"
#include "Entity.h"
#include <vector>
#include <memory>

class MapManager
{
public:
	MapManager();

	void CheckCollisionsAndMove(std::shared_ptr<Player>& player, int x, int y);
	void RenderLevel(std::vector<std::shared_ptr<Entity>>& entities);

private:
	ConsoleHelper* cHelper;

	char GetNextPosition(int posX, int posY, int movementX, int movementY);
	void CreateRoom(int height, int width);
	void RenderElement(int x, int y, char element);
};

