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

// Me la rob� de un grone en StackOverflow
// Supuestamente me da el caracter de donde est� el cursor
// Esto probablemente funcione solo en Windows, asi que si ten�s problemas ya sab�s donde es
// Quiz�s en Mac puedas usar ncurses.h
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
    char character = get_next_position(player->GetPosX(), player->GetPosY(), x, y);

    switch (character) {
        case '.':
            player->Move(x, y);
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
    render_element(player->GetPosX(), player->GetPosY(), '0');
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
