#include "GameManager.h"

using namespace std;

//void render_hud(Player player)
//{
//    printf("Level: %d Hits:%d(%d) Str:%d(%d) Gold:%d Armor:%d Exp:%d/%d", player.level, player.currentHitPoints, player.hitPoints, player.currentStrength, player.strength, player.gold, player.armor, player.currentExperience, player.experience);
//}
//
//void render_canvas()
//{
//}

int main()
{
	GameManager* gameManager = new GameManager();

	gameManager->StartGame();
}

//
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//class Coordinate
//{
//public:
//    Coordinate(int x, int y);
//    ~Coordinate();
//    int x;
//    int y;
//
//private:
//
//};
//
//Coordinate::Coordinate(int x, int y) : x(x), y(y)
//{
//}
//
//Coordinate::~Coordinate()
//{
//}
//
//class Rectangle
//{
//public:
//    Rectangle(Coordinate origin, Coordinate end);
//    ~Rectangle();
//    Coordinate origin;
//    Coordinate end;
//
//private:
//
//};
//
//Rectangle::Rectangle(Coordinate origin, Coordinate end) : origin(origin), end(end)
//{
//}
//
//Rectangle::~Rectangle()
//{
//}
//
//void draw_rectangle(Rectangle rectangle) {
//    for (int i = rectangle.origin.y; i < rectangle.end.y; i++)
//    {
//        for (int j = rectangle.origin.x; j < rectangle.end.x; j++)
//        {
//            if (i == rectangle.origin.x || i == rectangle.end.x - 1 || j == rectangle.origin.y || j == rectangle.end.y - 1) {
//                cout << "#";
//            }
//            else {
//                cout << ".";
//            }
//        }
//
//        cout << endl;
//    }
//}
//
//class Node
//{
//public:
//    Node(Rectangle rectangle);
//    ~Node();
//    Rectangle rectangle;
//    Node* left;
//    Node* right;
//private:
//
//};
//
//Node::Node(Rectangle rectangle) : rectangle(rectangle), left(nullptr), right(nullptr)
//{
//}
//
//Node::~Node()
//{
//}
//
//void drawRectangles(const vector<Rectangle>& rectangles) {
//    const int gridWidth = 20;
//    const int gridHeight = 20;
//    char grid[gridHeight][gridWidth];
//
//    // Initialize grid
//    for (int i = 0; i < gridHeight; ++i) {
//        for (int j = 0; j < gridWidth; ++j) {
//            grid[i][j] = ' ';
//        }
//    }
//
//    // Draw rectangles
//    char rectChar = 'A';
//    for (const auto& rect : rectangles) {
//        for (int i = rect.origin.y; i < rect.end.y; ++i) {
//            for (int j = rect.origin.x; j < rect.end.x; ++j) {
//                grid[i][j] = rectChar;
//            }
//        }
//        rectChar++;
//        if (rectChar > 'Z') rectChar = 'A'; // Wrap around if we run out of characters
//    }
//
//    // Print grid
//    for (int i = 0; i < gridHeight; ++i) {
//        for (int j = 0; j < gridWidth; ++j) {
//            cout << grid[i][j];
//        }
//        cout << endl;
//    }
//}
//
//void collectRectangles(Node* node, vector<Rectangle>& rectangles) {
//    if (node == nullptr) return;
//    rectangles.push_back(node->rectangle);
//    collectRectangles(node->left, rectangles);
//    collectRectangles(node->right, rectangles);
//}
//
//void partition(Node* node, int depth) {
//    if (depth == 3) {
//        return;
//    }
//
//    bool vertical = depth % 2 == 0;
//
//    if (vertical) {
//        Rectangle left_rectangle(Rectangle(Coordinate(node->rectangle.origin.x, node->rectangle.origin.y), Coordinate(node->rectangle.end.x, node->rectangle.end.y / 2)));
//        Rectangle right_rectangle(Rectangle(Coordinate(node->rectangle.end.x, node->rectangle.end.y / 2), Coordinate(node->rectangle.end.x, node->rectangle.end.y)));
//
//        node->left = new Node(left_rectangle);
//        node->right = new Node(right_rectangle);
//
//        partition(node->left, depth + 1);
//        partition(node->right, depth + 1);
//    }
//    else {
//        Rectangle left_rectangle(Rectangle(Coordinate(node->rectangle.origin.x, node->rectangle.origin.y), Coordinate(node->rectangle.end.x / 2, node->rectangle.end.y)));
//        Rectangle right_rectangle(Rectangle(Coordinate(node->rectangle.end.x / 2, node->rectangle.origin.y), Coordinate(node->rectangle.end.x, node->rectangle.end.y)));
//
//        node->left = new Node(left_rectangle);
//        node->right = new Node(right_rectangle);
//
//        partition(node->left, depth + 1);
//        partition(node->right, depth + 1);
//    }
//}
//
//int main()
//{
//    Rectangle rectangle(Coordinate(0, 0), Coordinate(15, 15));
//
//    Node node(rectangle);
//
//    partition(&node, 0);
//
//    //draw_rectangle(node.right->rectangle);
//    vector<Rectangle> rectangles;
//    collectRectangles(&node, rectangles);
//
//    drawRectangles(rectangles);
//
//
//    std::cout << "Hello World!\n";
//}