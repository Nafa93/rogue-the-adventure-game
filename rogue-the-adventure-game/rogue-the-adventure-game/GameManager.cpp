#include "GameManager.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

GameManager::GameManager() : 
    player(2, 2), 
    mapManager()
{
	exitGame = false;
    cHelper = ConsoleHelper::GetInstance();
}

void GameManager::StartGame() {
    InitialSetup();
    GameLoop();
}

void GameManager::HandleUserInput(bool* salida)
{
    if (_kbhit()) {
        char l = _getch();
        int ascii = (int)l;

        switch (ascii)
        {
            // ESC
        case 27:
            *salida = true;
            break;
            // A
        case 97:
            mapManager.CheckCollisionsAndMove(&player, -1, 0);
            break;
            // D
        case 100:
            mapManager.CheckCollisionsAndMove(&player, 1, 0);
            break;
            // S
        case 115:
            mapManager.CheckCollisionsAndMove(&player, 0, 1);
            break;
            // W
        case 119:
            mapManager.CheckCollisionsAndMove(&player, 0, -1);
            break;
        }
    }
}

void GameManager::InitialSetup()
{
    cHelper->HideCursor();
}

void GameManager::GameLoop() 
{
    while (!exitGame) {

        system("cls");

        mapManager.RenderLevel(player);

        HandleUserInput(&exitGame);

        Sleep(70);
    }
}