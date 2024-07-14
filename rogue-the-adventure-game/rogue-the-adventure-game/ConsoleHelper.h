#pragma once
#include <Windows.h>
#include <iostream>

class ConsoleHelper
{
protected:
	static ConsoleHelper* consoleHelper_;
	COORD previousCursorPosition;

	ConsoleHelper() 
	{
		previousCursorPosition = { 0, 0 };
	}

public:

    ConsoleHelper(ConsoleHelper& other) = delete;

    void operator=(const ConsoleHelper&) = delete;

	static ConsoleHelper* GetInstance();

	char CharRead();
	void HideCursor();
	void MoveCursorToPreviousPosition();
	void PrintElementOnPosition(int x, int y, char element);
	void SetCursorPosition(int x, int y);
	void ChangeColor(int ForgC);
};

