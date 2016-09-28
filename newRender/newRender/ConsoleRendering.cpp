#include "ConsoleRendering.h"
#include <iostream>

///////////////////////////////////////////////////////
// Consoe rendering code developed by Marcus Franzen //
///////////////////////////////////////////////////////

namespace ConsoleRendering
{
	//The default width of the screen.
	static int SCREEN_WIDTH = 64;
	//The default height of the screen.
	static int SCREEN_HEIGHT = 16;

	static HANDLE CONSOLE_HANDLE = NULL;

	//Our array buffer for the screen.
	static std::string* ScreenBufferArray;
	static bool* ScreenBufferStateArray;

	void Initialize(int screenWidth, int screenHeight)
	{

		SCREEN_WIDTH = screenWidth;
		SCREEN_HEIGHT = screenHeight;

		//Get the handle to the console.
		CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

		//Allocate a new array of our screen size.
		ScreenBufferArray = new std::string[SCREEN_HEIGHT];
		ScreenBufferStateArray = new bool[SCREEN_HEIGHT];

		SetCursorVisible(false);

		SetConsoleWindowSize(SCREEN_WIDTH + 2, SCREEN_HEIGHT + 2);
		SetConsoleBufferSize(SCREEN_WIDTH + 2, SCREEN_HEIGHT + 2);

		//Set the title of our console window and maximize it.
		SetConsoleTitle(TEXT("ConsoleRendering"));
		HWND hWnd = FindWindow(NULL, TEXT("ConsoleRendering"));
		ShowWindow(hWnd, SW_MAXIMIZE);

		InitializeScreenBuffer();
	}

	void Render()
	{
		//Reset the console cursor to position x:0 y:0
		const COORD cursorOrigo = {0, 0};
		SetConsoleCursorPosition(CONSOLE_HANDLE, cursorOrigo);

		//Offset our buffer by 1 row
		std::cout << std::endl;

		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			std::string screenBufferRow = std::string("\n");

			if(ScreenBufferStateArray[y])
			{
				//Offset our buffer by 1 column

				screenBufferRow = std::string(" ") + ScreenBufferArray[y] + screenBufferRow;
			}

			fwrite(screenBufferRow.c_str(), screenBufferRow.length(), 1, stderr);
		}

		ResetScreenBufferStates();
	}


	void DrawToScreenBuffer(int x, int y, char character)
	{
		//return without rendering if we try to render outside of the screen boundaries.
		if(x < 0 || x >= SCREEN_WIDTH) return;
		if(y < 0 || y >= SCREEN_HEIGHT) return;

		if(ScreenBufferArray[y][x] != character)
		{
			ScreenBufferStateArray[y] = true;
		}

		ScreenBufferArray[y][x] = character;
	}

	char GetFromScreenBuffer(int x, int y)
	{
		//returns whitespace if we request chars outside of the screen buffers bounds.
		if(x < 0 || x >= SCREEN_WIDTH) return ' ';
		if(y < 0 || y >= SCREEN_HEIGHT) return ' ';

		return ScreenBufferArray[y][x];
	}

	void ClearScreenBuffer()
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			for (int y = 0; y < SCREEN_HEIGHT; y++)
			{
				DrawToScreenBuffer(x, y, ' ');
			}
		}
	}

	int GetScreenWidth()
	{
		return SCREEN_WIDTH;
	}

	int GetScreenHeight()
	{
		return SCREEN_WIDTH;
	}


	void SetCursorVisible(bool isVisible)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(CONSOLE_HANDLE, &cursorInfo);
		//Set the cursors visibility.
		cursorInfo.bVisible = isVisible;
		SetConsoleCursorInfo(CONSOLE_HANDLE, &cursorInfo);
	}

	void SetConsoleWindowSize(int width, int height)
	{
		_SMALL_RECT Size;
		Size.Top = 0;
		Size.Left = 0;
		Size.Bottom = height-1;
		Size.Right = width-1;

		SetConsoleWindowInfo(CONSOLE_HANDLE, TRUE, &Size);
	}

	void SetConsoleBufferSize(int width, int height)
	{
		COORD size;
		size.X = width;
		size.Y = height;

		SetConsoleScreenBufferSize(CONSOLE_HANDLE, size);
	}

	void InitializeScreenBuffer()
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			ScreenBufferArray[y] = "";
			for (int x = 0; x < SCREEN_WIDTH; x++)
			{
				ScreenBufferArray[y] += ' ';
			}
		}
	}

	void ResetScreenBufferStates()
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			ScreenBufferStateArray[y] = false;
		}
	}
}