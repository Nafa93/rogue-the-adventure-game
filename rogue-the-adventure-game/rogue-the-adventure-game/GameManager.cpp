#include "GameManager.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Player.h"
#include "Enemy.h"
#include <memory>

GameManager::GameManager() :
    mapManager()
{
	exitGame = false;
    cHelper = ConsoleHelper::GetInstance();
}

void GameManager::StartGame() {
    InitialSetup();
    GameLoop();
}

void GameManager::HandleUserInput(bool* exit)
{
    if (_kbhit()) {
        char l = _getch();
        int ascii = (int)l;

        for (auto& entity : entities) {
            if (auto player = std::dynamic_pointer_cast<Player>(entity)) {
                switch (ascii)
                {
                    // ESC
                case 27:
                    *exit = true;
                    break;
                    // A
                case 97:
                    mapManager.CheckCollisionsAndMove(player, -1, 0);
                    break;
                    // D
                case 100:
                    mapManager.CheckCollisionsAndMove(player, 1, 0);
                    break;
                    // S
                case 115:
                    mapManager.CheckCollisionsAndMove(player, 0, 1);
                    break;
                    // W
                case 119:
                    mapManager.CheckCollisionsAndMove(player, 0, -1);
                    break;
                }
            }
        }
    }
}

void GameManager::RenderHud(std::shared_ptr<Player>& player)
{
    printf("Level: %d Hits:%d(%d) Str:%d Gold:%d Armor:%d Exp:%d/%d", player->level, player->currentHitPoints, player->hitPoints, player->strength, player->gold, player->armor, player->currentExperience, player->experience);
}

void GameManager::RenderScene() 
{
    mapManager.RenderLevel(entities);
    
    for (auto& entity : entities) {
        if (auto player = std::dynamic_pointer_cast<Player>(entity)) {
            RenderHud(player);
        }
    }
}

void GameManager::InitialSetup()
{
    mapManager.InitializeMap();

    entities.push_back(make_shared<Player>(2, 2));
    entities.push_back(make_shared<Enemy>(5, 5, 10, 10, 1, 0, 1, 'S', "Snake"));

    cHelper->HideCursor();
}

void GameManager::GameLoop() 
{
    while (!exitGame) {

        system("cls");

        RenderScene();
        
        Update();

        HandleUserInput(&exitGame);

        Sleep(70);
    }
}

void GameManager::Update()
{
    std::shared_ptr<Player> player = nullptr;

    for (auto& entity : entities) {
        if (auto playerPointer = std::dynamic_pointer_cast<Player>(entity)) {
            player = playerPointer;
            break;
        }
    }

    for (auto& entity : entities) {
        if (auto enemy = std::dynamic_pointer_cast<Enemy>(entity)) {
            enemy->MoveOrAttack(player);
        }
    }
}
