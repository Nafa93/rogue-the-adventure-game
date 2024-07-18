#include <vector>
#include <memory>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "MapManager.h"
#include "Player.h"
#include "ConsoleHelper.h"
#include "Entity.h"
#include "Coordinate.h"
#include "Rectangle.h"
#include "Tree.h"
#include "Node.h"
#include "Canvas.h"

MapManager::MapManager() {
    cHelper = ConsoleHelper::GetInstance();
}

void MapManager::InitializeRoom(int height, int width) {
    room.resize(height);
    for (int i = 0; i < height; ++i) {
        room[i].resize(width, '.');  // Inicializa el cuarto con '.' por defecto
    }
}

void MapManager::RenderLevel(std::vector<std::shared_ptr<Entity>>& entities)
{
    for (const auto& row : room) {
        for (char cell : row) {
            if (cell == '#') {
                cHelper->ChangeColor(100);
            }
            else {
                cHelper->ChangeColor(255);
            }
            printf("%c", cell);
        }
        std::cout << std::endl;
    }

    for (const auto& entity : entities) {
        RenderElement(entity->GetPosX(), entity->GetPosY(), entity->GetSprite());
    }
    
}

void MapManager::InitializeMap()
{
    //CreateRoom(20, 20);

    int height = 60;
    int width = 180;

    Tree tree(Node(RectangleShape(Coordinate(0, 0), height, width)));

    tree.partition(&tree.root, 0, 3);

    tree.generate_corridors(&tree.root);

    Canvas canvas(height, width);

    canvas.add_corridors(tree.corridors, '$');

    canvas.add_rectangles(tree.rooms, '#');

    room = canvas.data;
}

char MapManager::GetNextPosition(int posX, int posY, int movementX, int movementY)
{
    char nextPosition;

    cHelper->SetCursorPosition(posX + movementX, posY + movementY);
    nextPosition = cHelper->CharRead();
    cHelper->SetCursorPosition(posX, posY);

    return nextPosition;
}

void MapManager::CreateRoom(int height, int width) {
    InitializeRoom(height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((i == 0) || (j == 0) || (i == height - 1) || (j == width - 1)) {
                room[i][j] = '#';
            }
            else {
                room[i][j] = '.';
            }
        }
    }
}

void MapManager::RenderElement(int x, int y, char element)
{
    cHelper->ChangeColor(50);
    cHelper->PrintElementOnPosition(x, y, element);
}


