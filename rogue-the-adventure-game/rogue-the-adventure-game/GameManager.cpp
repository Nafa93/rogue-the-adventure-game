#include "GameManager.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Player.h"
#include "Enemy.h"
#include "Consumable.h"
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
    printf("Hits:%d(%d) Str:%d Armor:%d", player->currentHitPoints, player->hitPoints, player->strength, player->armor);
}

void GameManager::InitializeStaticMap(ScreenBuffer& screen) {
    mapManager.RenderStaticMap(screen);
}

void GameManager::RenderScene(ScreenBuffer& screen)
{
    mapManager.RenderDynamicElements(screen, entities);
    
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

    addSnakes(10);

    addTrolls(5);

    addZombies(3);

    addPotions(3);

    addAttackBoosts(1);

    addDefenseBoosts(1);

    cHelper->HideCursor();
}

void GameManager::addZombies(int quantity)
{
    for (int i = 0; i < quantity; i++) {
        Coordinate zombieOrigin = mapManager.GetRandomRoom().get_random_coordinate();

        entities.push_back(Enemy::zombie(zombieOrigin.x, zombieOrigin.y));
    }
}

void GameManager::addTrolls(int quantity)
{
    for (int i = 0; i < quantity; i++) {
        Coordinate trollOrigin = mapManager.GetRandomRoom().get_random_coordinate();

        entities.push_back(Enemy::troll(trollOrigin.x, trollOrigin.y));
    }
}

void GameManager::addSnakes(int quantity)
{
    for (int i = 0; i < quantity; i++) {

        Coordinate snakeOrigin = mapManager.GetRandomRoom().get_random_coordinate();

        entities.push_back(Enemy::snake(snakeOrigin.x, snakeOrigin.y));
    }
}

void GameManager::addPotions(int quantity)
{
    for (int i = 0; i < quantity; i++) {
        Coordinate potionOrigin = mapManager.GetRandomRoom().get_random_coordinate();

        entities.push_back(Consumable::potion(potionOrigin.x, potionOrigin.y));
    }
}

void GameManager::addDefenseBoosts(int quantity)
{
    for (int i = 0; i < quantity; i++) {
        Coordinate defenseBoostOrigin = mapManager.GetRandomRoom().get_random_coordinate();

        entities.push_back(Consumable::armor(defenseBoostOrigin.x, defenseBoostOrigin.y));
    }
}

void GameManager::addAttackBoosts(int quantity)
{
    for (int i = 0; i < quantity; i++) {
        Coordinate attackBoostOrigin = mapManager.GetRandomRoom().get_random_coordinate();

        entities.push_back(Consumable::strength(attackBoostOrigin.x, attackBoostOrigin.y));
    }
}

void GameManager::GameLoop()
{
    bool playerUsedAction = false;
    ScreenBuffer screen(180, 50);

    InitializeStaticMap(screen);

    while (!exitGame) {

        screen.ResetDynamicBuffer();

        RenderScene(screen);

        screen.Render();
        
        Update(playerUsedAction);

        playerUsedAction = false;

        HandleUserInput(&exitGame, &playerUsedAction);

        Sleep(30);
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
