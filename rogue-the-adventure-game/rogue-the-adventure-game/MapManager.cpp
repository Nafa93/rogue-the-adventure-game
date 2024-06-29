#include "MapManager.h"
#include "Player.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

MapManager::MapManager() {
    cHelper = ConsoleHelper::GetInstance();
}

void MapManager::CheckCollisionsAndMove(Player* player, int x, int y) 
{
    char character = GetNextPosition(player->GetPosX(), player->GetPosY(), x, y);

    switch (character) {
    case '.':
        player->Move(x, y);
        break;
    default:
        break;
    }
}

void MapManager::RenderLevel(Player player)
{
    CreateRoom(10, 10);
    RenderElement(player.GetPosX(), player.GetPosY(), '0');
}

char MapManager::GetNextPosition(int posX, int posY, int movementX, int movementY)
{
    char nextPosition;

    cHelper->SetCursorPosition(posX + movementX, posY + movementY);
    nextPosition = cHelper->CharRead();
    cHelper->SetCursorPosition(posX, posY);

    return nextPosition;
}

void MapManager::CreateRoom(int height, int width)
{

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            if ((i == 0) || (j == 0) || (i == height - 1) || (j == width - 1))
            {
                cHelper->ChangeColor(100);
                printf("#");
            }
            else
            {
                cHelper->ChangeColor(255);
                printf(".");
            }

        }

        std::cout << std::endl;
    }
}

void MapManager::RenderElement(int x, int y, char element)
{
    cHelper->ChangeColor(50);
    cHelper->SetCursorPosition(x, y);
    std::cout << element;
}


