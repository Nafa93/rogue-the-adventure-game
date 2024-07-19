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
#include "RectangleShape.h"
#include "Tree.h"
#include "Node.h"
#include "Canvas.h"

using namespace std;

MapManager::MapManager() {
    cHelper = ConsoleHelper::GetInstance();
}

void MapManager::RenderLevel(vector<shared_ptr<Entity>>& entities)
{
    for (const auto& row : data) {
        for (char cell : row) {
            if (cell == '#') {
                cHelper->ChangeColor(100);
            }
            else {
                cHelper->ChangeColor(255);
            }
            printf("%c", cell);
        }
        
        cout << endl;
    }

    for (const auto& entity : entities) {
        RenderElement(entity->GetPosX(), entity->GetPosY(), entity->GetSprite());
    }
    
}

void MapManager::InitializeMap()
{
    int height = 60;
    int width = 180;

    Tree tree(Node(RectangleShape(Coordinate(0, 0), height, width)));

    tree.partition(&tree.root, 0, 3);

    tree.generate_corridors(&tree.root);

    Canvas canvas(height, width);

    canvas.add_corridors(tree.corridors, '$');

    canvas.add_rectangles(tree.rooms, '#');

    rooms = tree.rooms;

    mainRoom = rooms[0];

    otherRooms = vector<RectangleShape>(rooms.begin() + 1, rooms.end());

    data = canvas.data;
}

char MapManager::GetNextPosition(int posX, int posY, int movementX, int movementY)
{
    char nextPosition;

    cHelper->SetCursorPosition(posX + movementX, posY + movementY);
    nextPosition = cHelper->CharRead();
    cHelper->SetCursorPosition(posX, posY);

    return nextPosition;
}

RectangleShape MapManager::GetRandomRoom()
{
    int random_index = rng.generate(0, otherRooms.size());

    return otherRooms[random_index];
}

void MapManager::RenderElement(int x, int y, char element)
{
    cHelper->ChangeColor(50);
    cHelper->PrintElementOnPosition(x, y, element);
}