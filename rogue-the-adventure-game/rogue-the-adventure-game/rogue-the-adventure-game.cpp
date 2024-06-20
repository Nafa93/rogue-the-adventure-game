#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

class Player
{
public:
    int level;
    int hitPoints;
    int currentHitPoints;
    int strength;
    int currentStrength;
    int gold;
    int armor;
    int experience;
    int currentExperience;
    int posY;
    int posX;

    Player(int x, int y)
    {
        level = 1;
        hitPoints = 100;
        currentHitPoints = 100;
        strength = 10;
        currentStrength = 10;
        gold = 0;
        armor = 10;
        experience = 10;
        currentExperience = 0;
        posX = x;
        posY = y;
    }

    void Move(int x, int y) 
    {
        this->posY += y;
        this->posX += x;
    }

    int GetPosX()
    {
        return this->posX;
    }

    int GetPosY()
    {
        return this->posY;
    }
};

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
                printf("#");
            }
            else
            {
                printf(".");
            }
        }
        cout << endl;
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
            player->Move(-1, 0);
            break;
            // D
        case 100:
            player->Move(1, 0);
            break;
            // S
        case 115:
            player->Move(0, 1);
            break;
            // W
        case 119:
            player->Move(0, -1);
            break;
        }
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

void render_element(int x, int y, char element) 
{
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
    render_element(player->GetPosX(), player->GetPosY(), '0');
}

int main()
{
    Player player(2, 2);
    bool exitGame = false;

    while (!exitGame) {
        system("cls");

        handle_user_input(&exitGame, &player);

        render_level(&player);

        Sleep(20);
    }
}
