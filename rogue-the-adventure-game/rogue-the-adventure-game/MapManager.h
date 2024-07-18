#pragma once
#include "Player.h"
#include "ConsoleHelper.h"
#include <vector>
#include <memory>

class Entity;

class MapManager
{
public:
	MapManager();

	void InitializeRoom(int height, int width);
	void RenderLevel(std::vector<std::shared_ptr<Entity>>& entities);
	void InitializeMap();
	char GetNextPosition(int posX, int posY, int movementX, int movementY);

private:
	ConsoleHelper* cHelper;
	std::vector<std::vector<char>> room;

	void CreateRoom(int height, int width);
	void RenderElement(int x, int y, char element);
};

