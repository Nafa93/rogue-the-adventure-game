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

void MapManager::RenderStaticMap(ScreenBuffer& screen) {
    for (int y = 0; y < data.size(); ++y) {
        for (int x = 0; x < data[y].size(); ++x) {
            screen.DrawStaticBuffer(x, y, data[y][x]);
        }
    }
}

void MapManager::RenderDynamicElements(ScreenBuffer& screen, const std::vector<std::shared_ptr<Entity>>& entities) {
    for (const auto& entity : entities) {
        RenderElement(screen, entity->GetPosX(), entity->GetPosY(), entity->GetSprite());
    }
}

void MapManager::InitializeMap()
{
    int height = 50;
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

char MapManager::GetNextPosition(int posX, int posY, int movementX, int movementY) {
    return data[posY + movementY][posX + movementX];
}

RectangleShape MapManager::GetRandomRoom()
{
    int random_index = rng.generate(0, otherRooms.size() - 1);

    return otherRooms[random_index];
}

void MapManager::RenderElement(ScreenBuffer& screen, int x, int y, char element) {
    screen.Draw(x, y, element);
}