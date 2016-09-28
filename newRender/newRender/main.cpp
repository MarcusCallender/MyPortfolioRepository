//#include "ConsoleRendering.h"
//#include <iostream>
//#include <time.h>
//#include <string>
//#include <math.h>
//
//static const int FRAME_DELAY_MILLISECONDS = 1000/24;
//static const float FRAME_DELAY_SECONDS = FRAME_DELAY_MILLISECONDS*0.001f;
//
//float totalTime = 0.0f;
//
////Input variables.
//float zoom = 10.0f;
//float xOffset = 0.0f;
//float yOffset = 0.0f;
//const int screenHeight = 16, screenWidth = 64;
//const float jumpHeight = 6;
//const int maxRocks = screenWidth * screenHeight - 1, COUNTDOWN_TIME = 60;
//const int scorePos = 0, timePos = 40;
//
//float xPos = 0.0f, yPos = screenHeight - 1, jumpCieling = 0;
//float RxPos = 0.0f, RyPos = 0.0f, rockTwinkleAndFloat = true;
//bool grounded = true, jumping = false, newStar = true, toExit = false;
//int fallenRockAmmount = 0, countdown = COUNTDOWN_TIME, stars = 0;
//float fallenRocks [maxRocks] [2];
//std::string timeMessage = "Time Remaining: ", scoreMessage = "Stars: ";
//
//const int maxStars = 10;
//int fallingStars = 0;
//float starPositions [maxStars] [2];
//bool starTwinkleAndFloat [maxStars];
//
////Function to get keyboard inputs using windows GetASyncKeyState.
////The vKey parameter below is a virtual-key in Windows. there's a list of Virtual Keys that you can use here: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
//bool IsKeyDown(int vKey);
//
////Handle our inputs from the keyboard, apply to our user variables.
//void HandleInput();
//
////An intro sequence that writes instructions to the user and halts our program.
//void IntroSequence();
//
//void Initialize();
//void Update();
//void Render();
//
//void JumpManager();
//void spawnStar();
//void moveStar();
//bool seeFallenStars(int inX, int inY);
//int printWord(std::string word, int rendererPos);
//bool airCollision(int move);
//int printNumber (int number, int rendererPos);
//void gameOver ();
////void smoothMovement(float move, float &position, float &counter);
//
//int main()
//{
//	Initialize();
//
//	while(true)
//	{
//		Update();
//		if (toExit) {
//			std::cout << "Bye! (^^)/\t";
//			break;
//		}
//		Render();
//
//		Sleep(FRAME_DELAY_MILLISECONDS);
//	}
//
//	return 0;
//}
//
//void Initialize()
//{
//	//Run the intro sequence before starting the rendering.
//	IntroSequence();
//
//	//Initialize our ConsoleRendering library with a screen width and height of 64
//	ConsoleRendering::Initialize(screenWidth, screenHeight);
//	srand((unsigned int) time(0));
//}
//
//void Update()
//{
//	//Increment the total time our program has been running.
//	totalTime += FRAME_DELAY_SECONDS;
//	countdown = 60 - (int) totalTime;
//
//	if (xPos == RxPos && yPos == RyPos) {
//		newStar = true;
//		stars++;
//	}
//
//	if (newStar) {
//		spawnStar();
//	} else {
//		moveStar();
//	}
//
//	HandleInput();
//
//	if (!grounded) {
//		JumpManager();
//	}
//
//	for (int y = 0; y < screenHeight; y++) {
//		for (int x = 0; x < screenWidth; x++) {
//			if (x == scorePos && y == 0) {
//				x = printWord(scoreMessage, x);
//				x = printNumber(stars, x);
//			} else if (x == timePos && y == 0) {
//				x = printWord(timeMessage, x);
//				x = printNumber(countdown, x);
//			} else if (x == xPos && y == yPos) {
//				ConsoleRendering::DrawToScreenBuffer(x, y, '^');
//			} else if (seeFallenStars(x, y)) {
//				ConsoleRendering::DrawToScreenBuffer(x, y, '#');
//			} else if (!newStar && (x == RxPos && y == RyPos)) {
//				if (!rockTwinkleAndFloat) {
//					ConsoleRendering::DrawToScreenBuffer(x, y, '*');
//				} else {
//					ConsoleRendering::DrawToScreenBuffer(x, y, '+');
//				}
//			} else {
//				ConsoleRendering::DrawToScreenBuffer(x, y, ' ');
//			}
//		}
//	}
//
//	if (totalTime >= COUNTDOWN_TIME) {
//		gameOver();
//	}
//}
//
//void Render()
//{
//	ConsoleRendering::Render();
//}
//
//bool IsKeyDown(int key)
//{
//	return (GetAsyncKeyState(key) & 0x8000) != 0;
//}
//
//void HandleInput()
//{
//	//The amount we will move per frame.
//	float movementSpeed = FRAME_DELAY_SECONDS*13.0f;
//
//	//The amount we will zoom per frame.
//	float zoomSpeed = FRAME_DELAY_SECONDS*4.0f;
//
//	if (IsKeyDown('D')) {
//		if (xPos != screenWidth - 1 && !airCollision(1)) {
//			xPos++;
//			if (!seeFallenStars((int) xPos, (int) (yPos + 1)) && yPos < screenHeight - 1) {
//				grounded = false;
//			}
//		}
//	} else if (IsKeyDown('A')) {
//		if (xPos != 0 && !airCollision(-1)) {
//			xPos--;
//			if (!seeFallenStars((int) xPos, (int) (yPos + 1)) && yPos < screenHeight - 1) {
//				grounded = false;
//			}
//		}
//	}
//
//	if (IsKeyDown(' ')) {
//		if (grounded) {
//			grounded = false;
//			jumping = true;
//			jumpCieling = yPos - jumpHeight;
//		}
//	}
//
//	if (IsKeyDown('Q')) {
//		toExit = true;
//	}
//}
//
//void IntroSequence()
//{
//	std::cout << "Collect as many stars as you can!\nUse 'A' and 'D' to move.\nUse and 'space' to jump.\nUse 'Q' to exit.\n";
//	system("Pause");
//	//clear the entire screen using system("cls") since we haven't Initialized ConsoleRendering yet.
//	system("cls");
//}
//
//
//void JumpManager () {
//	if (jumping) {
//		yPos--;
//		if (yPos == jumpCieling) {//ConsoleRendering::SCREEN_HEIGHT - jumpCieling
//			jumping = false;
//		}
//	} else {
//		yPos++;
//		if ((yPos == screenHeight - 1) || (seeFallenStars((int) xPos, (int) yPos + 1))) {
//			grounded = true;
//		}
//	}
//}
//
//void spawnStar () {
//	newStar = false;
//	int pos = 0;
//	pos = rand () % (int) screenWidth;
//	RxPos = (float) pos;
//	RyPos = 0.0f;
//	rockTwinkleAndFloat = true;
//}
//
//void moveStar () {
//	if (!rockTwinkleAndFloat) {
//		if (RyPos == screenHeight - 1 || seeFallenStars((int) RxPos, (int) RyPos + 1)) {
//			newStar = true;
//			fallenRocks[fallenRockAmmount][0] = RxPos;
//			fallenRocks[fallenRockAmmount][1] = RyPos;
//			fallenRockAmmount++;
//		}
//		RyPos++;
//		rockTwinkleAndFloat = true;
//	} else {
//		rockTwinkleAndFloat = false;
//	}
//}
//
//bool seeFallenStars (int inX, int inY) {
//	bool xMatch = false, yMatch = false;
//
//	for (int z = 0; z < fallenRockAmmount; z++) {
//		if (inX == fallenRocks[z][0]) {
//			xMatch = true;
//		}
//		if (inY == fallenRocks[z][1]) {
//			yMatch = true;
//		}
//
//		if (xMatch && yMatch) {
//			return true;
//		}
//		xMatch = false;
//		yMatch = false;
//	}
//
//	return false;
//}
//
//int printWord (std::string word, int rendererPos) {
//	for (int z = 0; z < (signed int) word.length(); z++) {
//		ConsoleRendering::DrawToScreenBuffer(rendererPos + z, 0, word[z]);
//	}
//
//	return rendererPos + word.length();
//}
//
//bool airCollision (int move) {
//	bool result = false;
//	if (!grounded && !jumping) {
//		result = seeFallenStars((int) (xPos + move), (int) (yPos + 1));
//	} else {
//		result = seeFallenStars((int) (xPos + move), (int) yPos);
//	}
//
//	return result;
//}
//
//int printNumber (int number, int rendererPos) {
//	char buffer [33];
//	int bufferToGoTo = 0;
//	_itoa_s(number, buffer, 10);
//
//	bufferToGoTo = printWord(buffer, rendererPos);
//	return bufferToGoTo;
//}
//
//void gameOver () {
//	system("cls");
//	std::cout << "Well done You managed to get " << stars << " stars!\n";
//	toExit = true;
//}
//
//int findElement() {
//	bool xMatch, yMatch;
//
//	for (int z = 0; z < fallingStars; z++) {
//		xMatch = false, yMatch = false;
//
//		if (starPositions[z][0] == xPos) {
//			xMatch = true;
//		}
//		if (starPositions[z][0] == yPos) {
//			yMatch = true;
//		}
//		if (xMatch && yMatch) {
//			return z;
//		}
//	}
//
//	return 2002;
//}
//
//void moveAllongAndInsert (int inX, int inC) {
//	for (int z = inC; z > 0; z--) {
//		starPositions[z][0] = starPositions[z - 1][0];
//		starPositions[z][1] = starPositions[z - 1][1];
//	}
//
//	starPositions[0][0] = inX;
//	starPositions[0][1] = 0;
//}
//
///*void smoothMovement (float move, float &position, float &counter) {
//counter += move;
//position = floor(counter);
//}*/
