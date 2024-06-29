#pragma once
#include "MapManager.h"
#include "Player.h"
#include "ConsoleHelper.h"

class GameManager
{
public:
	bool exitGame;

	GameManager();

	void StartGame();

private:
	MapManager mapManager;
	Player player;
	ConsoleHelper* cHelper;

	void HandleUserInput(bool* salida);
	void InitialSetup();
	void GameLoop();
	void Update();
};

