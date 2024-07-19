#include "GameManager.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Player.h"
#include "Enemy.h"
#include <memory>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

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

void GameManager::HandleUserInput(bool* exit, bool* playerUsedAction)
{
    if (_kbhit()) {
        char l = _getch();
        int ascii = (int)l;

        int moveX = 0;
        int moveY = 0;

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
                    moveX = -1;
                    *playerUsedAction = true;
                    break;
                    // D
                case 100:
                    moveX = 1;
                    *playerUsedAction = true;
                    break;
                    // S
                case 115:
                    moveY = 1;
                    *playerUsedAction = true;
                    break;
                    // W
                case 119:
                    moveY = -1;
                    *playerUsedAction = true;
                    break;
                }

                player->MoveOrAttack(entities, moveX, moveY, &mapManager);
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

    Coordinate playerOrigin = mapManager.mainRoom.get_random_coordinate();

    entities.push_back(make_shared<Player>(playerOrigin.x, playerOrigin.y));

    Coordinate snakeOrigin = mapManager.GetRandomRoom().get_random_coordinate();

    entities.push_back(Enemy::snake(snakeOrigin.x, snakeOrigin.y));

    Coordinate trollOrigin = mapManager.GetRandomRoom().get_random_coordinate();

    entities.push_back(Enemy::troll(trollOrigin.x, trollOrigin.y));

    Coordinate zombieOrigin = mapManager.GetRandomRoom().get_random_coordinate();

    entities.push_back(Enemy::zombie(zombieOrigin.x, zombieOrigin.y));

    cHelper->HideCursor();
}

void GameManager::GameLoop() 
{
    bool playerUsedAction = false;

    while (!exitGame) {

        system("cls");

        RenderScene();
        
        Update(playerUsedAction);

        playerUsedAction = false;

        HandleUserInput(&exitGame, &playerUsedAction);

        Sleep(70);
    }
}

void GameManager::Update(bool playerUsedAction)
{
    if (!playerUsedAction) return;

    std::shared_ptr<Player> player = nullptr;

    for (auto& entity : entities) {
        if (auto playerPointer = std::dynamic_pointer_cast<Player>(entity)) {
            player = playerPointer;
            break;
        }
    }

    for (auto& entity : entities) {
        if (auto enemy = std::dynamic_pointer_cast<Enemy>(entity)) {
            if (enemy->IsAlive()) {
                enemy->MoveOrAttack(entities, player->GetPosX(), player->GetPosY(), &mapManager);
            }
        }
    }

    entities.erase(std::remove_if(entities.begin(), entities.end(), [](const std::shared_ptr<Entity>& entity) {
        return !entity->IsAlive();
    }), entities.end());
}
