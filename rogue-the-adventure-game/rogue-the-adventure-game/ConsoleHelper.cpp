#include "ConsoleHelper.h"
#include <Windows.h>
#include <iostream>

ConsoleHelper* ConsoleHelper::consoleHelper_ = nullptr;;

ConsoleHelper* ConsoleHelper::GetInstance()
{
    if (consoleHelper_ == nullptr) {
        consoleHelper_ = new ConsoleHelper();
    }
    return consoleHelper_;
}

// Lo saqué de stackoverflow
// Te dice el valor del caracter sobre el que está situado el cursor
// Creo que solo funca en Windows
char ConsoleHelper::CharRead()
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

void ConsoleHelper::HideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void ConsoleHelper::SetCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

void ConsoleHelper::ChangeColor(int ForgC) {

    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}