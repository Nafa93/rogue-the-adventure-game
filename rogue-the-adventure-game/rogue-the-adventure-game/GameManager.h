#pragma once
#include "MapManager.h"
#include "ConsoleHelper.h"
#include "Entity.h"
#include "MessageManager.h"
#include <memory>
#include <vector>

using namespace std;

class GameManager
{
public:
	bool exitGame;

	GameManager();

	void StartGame();


private:
	MapManager mapManager;
	vector<shared_ptr<Entity>> entities;
	ConsoleHelper* cHelper;
	MessageManager messageManager;

	void RenderHud(std::shared_ptr<Player>& player);
	void InitializeStaticMap(ScreenBuffer& screen);
	void RenderScene(ScreenBuffer& screen);
	void InitialSetup();
	void GameLoop();
	void Update(bool playerUsedAction);
	void HandleUserInput(bool* exit, bool* playerUsedAction);
};

