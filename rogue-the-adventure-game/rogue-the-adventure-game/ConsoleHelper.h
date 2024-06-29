#pragma once
class ConsoleHelper
{
protected:
	static ConsoleHelper* consoleHelper_;

	ConsoleHelper() 
	{
	}

public:
    ConsoleHelper(ConsoleHelper& other) = delete;

    void operator=(const ConsoleHelper&) = delete;

	static ConsoleHelper* GetInstance();

	char CharRead();
	void HideCursor();
	void SetCursorPosition(int x, int y);
	void ChangeColor(int ForgC);
};

