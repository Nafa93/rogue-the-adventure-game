#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Player.h"

using namespace std;

void change_color(int ForgC) {

    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void render_hud(Player player)
{
    printf("Level: %d Hits:%d(%d) Str:%d(%d) Gold:%d Armor:%d Exp:%d/%d", player.level, player.currentHitPoints, player.hitPoints, player.currentStrength, player.strength, player.gold, player.armor, player.currentExperience, player.experience);
}

void render_canvas()
{
}

void create_room(int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i == 0) || (j == 0) || (i == height - 1) || (j == width - 1))
            {
                change_color(100);
                printf("#");
            }
            else
            {
                change_color(255);
                printf(".");
            }
        }
        cout << endl;
    }
}

void hide_cursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void set_cursor_position(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

// Me la robé de un grone en StackOverflow
// Supuestamente me da el caracter de donde está el cursor
// Esto probablemente funcione solo en Windows, asi que si tenés problemas ya sabés donde es
// Quizás en Mac puedas usar ncurses.h
char cursor_char_read()
{
    char buf[BUFSIZ];
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
    COORD pos = csbiInfo.dwCursorPosition; //set pos to current cursor location
    TCHAR strFromConsole[1];    //need space to only one char
    DWORD dwChars;
    ReadConsoleOutputCharacter(
        hConsole,
        strFromConsole, // Buffer where store symbols
        1, // Read 1 char to strFormConsole
        pos, // Read from current cursor position
        &dwChars); // How many symbols stored
    char c = strFromConsole[0];
    return c;
}

char get_next_position(int posX, int posY, int movementX, int movementY)
{
    char nextPosition;

    set_cursor_position(posX + movementX, posY + movementY);
    nextPosition = cursor_char_read();
    set_cursor_position(posX, posY);

    return nextPosition;
}

void check_collision_and_move(Player* player, int x, int y)
{
    char character = get_next_position(player->getPosX(), player->getPosY(), x, y);

    switch (character) {
        case '.':
            player->move(x, y);
            break;
        default:
            break;
    }
}

void handle_user_input(bool* salida, Player *player)
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
            check_collision_and_move(player, -1, 0);
            break;
            // D
        case 100:
            check_collision_and_move(player, 1, 0);
            break;
            // S
        case 115:
            check_collision_and_move(player, 0, 1);
            break;
            // W
        case 119:
            check_collision_and_move(player, 0, -1);
            break;
        }
    }
}

void render_element(int x, int y, char element) 
{
    change_color(50);
    set_cursor_position(x, y);
    cout << element;
}

void initial_setup() 
{
    hide_cursor();
}

void render_level(Player* player)
{
    create_room(10, 10);
    render_element(player->getPosX(), player->getPosY(), '0');
}



int main()
{
    Player player(2, 2);
    bool exitGame = false;

    initial_setup();

    while (!exitGame) {
        
        system("cls");

        render_level(&player);
        
        handle_user_input(&exitGame, &player);

        Sleep(70);
    }
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