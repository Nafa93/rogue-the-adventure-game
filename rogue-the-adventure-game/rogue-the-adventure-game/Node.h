#pragma once

#include "RectangleShape.h"

class Node
{
public:
    Node(RectangleShape rectangle) : rectangle(rectangle), room(rectangle), left(nullptr), right(nullptr) {};
    RectangleShape rectangle;
    RectangleShape room;
    Node* left;
    Node* right;
    bool has_children();
};