//#include "ConsoleRendering.h"
//#include <iostream>
//#include <time.h>
//#include <string>
//#include <math.h>
//
//static const int FRAME_DELAY_MILLISECONDS = 1000/24;
//static const float FRAME_DELAY_SECONDS = FRAME_DELAY_MILLISECONDS * 0.001f;
//
//float totalTime = 0.0f;
//
////Input variables.
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
//const int maxStars = 1;
//int fallingStars = 0;
//float starPositions [maxStars] [2];
//bool starTwinkleAndFloat [maxStars];
//bool toSpawn [maxStars];
//
//int fallingStars2 = 0;
//float starPositions2 [maxStars] [2];
//bool starTwinkleAndFloat2 [maxStars];
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
//void JumpManager ();
//void spawnStar ();
//void moveStar ();
//bool seeFallenStars (int inX, int inY);
//int printWord (std::string word, int rendererPos);
//bool airCollision (int move);
//int printNumber (int number, int rendererPos);
//void gameOver ();
//bool seeStars (int x, int y);
////void smoothMovement(float move, float &position, float &counter);
//void spawnStar2 ();
//void moveStar2 ();
//bool seeStars2 (int inX, int inY);
//bool checkSpawn ();
//
//int main()
//{
//	Initialize();
//
//	while(true)
//	{
//		Update();
//		if (toExit) {
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
//
//	for (int z = 0; z < maxStars; z++) {
//		toSpawn[z] = false;
//	}
//}
//
//void Update()
//{
//	//Increment the total time our program has been running.
//	totalTime += FRAME_DELAY_SECONDS;
//	countdown = 60 - (int) totalTime;
//
//	for (int z = 0; z < fallingStars; z++) {
//		if ((xPos == starPositions[z][0] || xPos + 1 == starPositions[z][0] || xPos - 1 == starPositions[z][0]) && 
//			(yPos == starPositions[z][1] || yPos + 1 == starPositions[z][1] || yPos - 1 == starPositions[z][1])) {
//				//newStar = true;
//				stars++;
//				fallingStars--;
//		}
//	}
//
//	if (checkSpawn()) { //newStar) {
//		spawnStar();
//	} else {
//		moveStar();
//	}
//
//	for (int z = 0; z < fallingStars2; z++) {
//		if ((xPos == starPositions2[z][0] || xPos + 1 == starPositions2[z][0] || xPos - 1 == starPositions2[z][0]) && 
//			(yPos == starPositions2[z][1] || yPos + 1 == starPositions2[z][1] || yPos - 1 == starPositions2[z][1])) {
//				//newStar = true;
//				stars++;
//				fallingStars2--;
//		}
//	}
//
//	if (fallingStars2 < maxStars) { //newStar) {
//		spawnStar2();
//	} else {
//		moveStar2();
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
//				//x = printWord("Falling stars: ", x);
//				//x = printNumber(fallingStars, x);
//			} else if (x == timePos && y == 0) {
//				x = printWord(timeMessage, x);
//				x = printNumber(countdown, x);
//			} else if (x == xPos && y == yPos) {
//				ConsoleRendering::DrawToScreenBuffer(x, y, '^');
//			} else if (seeFallenStars(x, y)) {
//				ConsoleRendering::DrawToScreenBuffer(x, y, '#');
//			} else if (seeStars(x, y)) {
//				if (!starTwinkleAndFloat[fallingStars - 1]) {
//					ConsoleRendering::DrawToScreenBuffer(x, y, '*');
//				} else {
//					ConsoleRendering::DrawToScreenBuffer(x, y, '+');
//				}
//			} else if (seeStars2(x, y)) {
//				if (!starTwinkleAndFloat2[fallingStars - 1]) {
//					ConsoleRendering::DrawToScreenBuffer(x, y, '\'');
//				} else {
//					ConsoleRendering::DrawToScreenBuffer(x, y, '^');
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
//		if (yPos == jumpCieling) {
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
//	//newStar = false;
//	int pos = 0;
//	pos = rand () % (int) screenWidth;
//	//RxPos = (float) pos;
//	starPositions[fallingStars][0] = (float) pos;
//	//RyPos = 0.0f;
//	starPositions[fallingStars][1] = 0.0f;
//	if (fallingStars % 2 == 0) {
//		starTwinkleAndFloat[fallingStars] = true;
//	} else {
//		starTwinkleAndFloat[fallingStars] = false;
//	}
//	fallingStars++;
//}
//
//void moveStar () {
//	int x = fallingStars;
//	for (int z = 0; z < x; z++) {
//		if (!starTwinkleAndFloat[z]) {
//			if (starPositions[z][1] == screenHeight - 1 || seeFallenStars((int) starPositions[z][0], (int) starPositions[z][1] + 1)) {
//				//newStar = true;
//				//fallenRocks[fallenRockAmmount][0] = RxPos;
//				fallenRocks [fallenRockAmmount] [0] = starPositions [z] [0];
//				//fallenRocks[fallenRockAmmount][1] = RyPos;
//				fallenRocks [fallenRockAmmount] [1] = starPositions [z] [1];
//				fallenRockAmmount++;
//				fallingStars--;
//			}
//			//RyPos++;
//			starPositions[z][1]++;
//			starTwinkleAndFloat[z] = true;
//		} else {
//			starTwinkleAndFloat[z] = false;
//		}
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
//
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
//	std::cout << "Well done You managed to get " << stars << " stars! (^^)/*\n";
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
//	starPositions[0][0] = (float) inX;
//	starPositions[0][1] = 0;
//}
//
///*void smoothMovement (float move, float &position, float &counter) {
//counter += move;
//position = floor(counter);
//}*/
//
//int deSpawningStar (float x, float y) {
//	return 0;
//}
//
//bool seeStars (int inX, int inY) {
//	bool xMatch = false, yMatch = false;
//
//	for (int z = 0; z < fallingStars; z++) {
//		if (inX == starPositions[z][0]) {
//			xMatch = true;
//		}
//
//		if (inY == starPositions[z][1]) {
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
//bool checkSpawn () {
//	for (int z = 0; z < maxStars; z++) {
//		if (toSpawn[z]) {
//			return true;
//		}
//	}
//	return false;
//}
//
//
//
//
//
//
//void spawnStar2 () {
//	//newStar = false;
//	int pos = 0;
//	pos = rand () % (int) screenWidth;
//	//RxPos = (float) pos;
//	starPositions2[fallingStars2][0] = (float) pos;
//	//RyPos = 0.0f;
//	starPositions2[fallingStars2][1] = 0.0f;
//	if (fallingStars2 % 2 == 0) {
//		starTwinkleAndFloat2[fallingStars2] = true;
//	} else {
//		starTwinkleAndFloat2[fallingStars2] = false;
//	}
//	fallingStars2++;
//}
//
//void moveStar2 () {
//	int x = fallingStars2;
//	for (int z = 0; z < x; z++) {
//		if (!starTwinkleAndFloat2[z]) {
//			if (starPositions2[z][1] == screenHeight - 1 || seeFallenStars((int) starPositions2[z][0], (int) starPositions2[z][1] + 1)) {
//				//newStar = true;
//				//fallenRocks[fallenRockAmmount][0] = RxPos;
//				fallenRocks [fallenRockAmmount] [0] = starPositions2 [z] [0];
//				//fallenRocks[fallenRockAmmount][1] = RyPos;
//				fallenRocks [fallenRockAmmount] [1] = starPositions2 [z] [1];
//				fallenRockAmmount++;
//				fallingStars2--;
//			}
//			//RyPos++;
//			starPositions2[z][1]++;
//			starTwinkleAndFloat2[z] = true;
//		} else {
//			starTwinkleAndFloat2[z] = false;
//		}
//	}
//}
//
//bool seeStars2 (int inX, int inY) {
//	bool xMatch = false, yMatch = false;
//
//	for (int z = 0; z < fallingStars2; z++) {
//		if (inX == starPositions2[z][0]) {
//			xMatch = true;
//		}
//
//		if (inY == starPositions2[z][1]) {
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