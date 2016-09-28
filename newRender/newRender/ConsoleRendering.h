#include <string>
#include "windows.h"

namespace ConsoleRendering
{
	//This should be ran at the top of your Initialize function.
	void Initialize(int screenWidth = 64, int screenHeight = 16);

	//Render our screen buffer to the console.
	//This should be ran in your Render function.
	void Render();


	//Draw a char to the screen buffer given a position and char.
	void DrawToScreenBuffer(int x, int y, char character);

	//Get a char from the screen buffer given a position.
	char GetFromScreenBuffer(int x, int y);

	//Clear the sceen buffer by rendering whitespace
	void ClearScreenBuffer();

	//Returns the width of the screen buffer
	int GetScreenWidth();

	//Returns the height of the screen buffer
	int GetScreenHeight();


	//Set the console cursors visibility.
	void SetCursorVisible(bool isVisible);

	//Set the console window size.
	void SetConsoleWindowSize(int width, int height);

	//Set the console buffer size.
	void SetConsoleBufferSize(int width, int height);

	//Initialize the screen buffer empty
	void InitializeScreenBuffer();

	//Reset the screen buffer state to keep track of what was rendered the current frame.
	void ResetScreenBufferStates();
}