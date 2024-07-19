#pragma once
#include "Player.h"
#include "ConsoleHelper.h"
#include "RectangleShape.h"
#include <vector>
#include <memory>

class Entity;

using namespace std;

class MapManager
{
public:
	MapManager();

	void RenderLevel(vector<shared_ptr<Entity>>& entities);
	void InitializeMap();
	char GetNextPosition(int posX, int posY, int movementX, int movementY);
	RectangleShape mainRoom;
	vector<RectangleShape> otherRooms;
	vector<RectangleShape> rooms;
	RectangleShape GetRandomRoom();

private:
	RandomNumberGenerator rng = RandomNumberGenerator();
	ConsoleHelper* cHelper;
	vector<vector<char>> data;

	void RenderElement(int x, int y, char element);
};

