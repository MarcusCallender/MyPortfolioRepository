#include "ConsoleRendering.h"
#include <iostream> //cout
#include <time.h> //time(0)
#include <string> //std::string type variables
#include <fstream>
#include <conio.h>

/////////////////////////////////////////////////
// This code was developed by Marcus Callender //
/////////////////////////////////////////////////

static const int FRAME_DELAY_MILLISECONDS = 1000/48;

//Deltatime also known as dt
static const float FRAME_DELAY_SECONDS = FRAME_DELAY_MILLISECONDS * 0.001f;

float totalTime = 0.0f;

//the height & whidth of the application
const int screenHeight = 16, screenWidth = 64;
//the ammount of units the player can jump
const float jumpHeight = 6.0f;
//the maximum ammount of rocks that can be spawned		the ammount of time the player has to collect stars
const int maxFallenStars = (screenWidth * screenHeight) - 1, COUNTDOWN_TIME = 30;
//the horizontal positions of the score and time indicators
const int scorePos = 0, timePos = 40;
//the ammount of frames the player will change there apperance for once they collect a star
const float seccondsPlayerChangedFor = 0.125f;
//the number of stars to be on the screen falling in any frame
const int maxStars = 5;
//messages informing the player of time remaining & stars collected
const std::string timeMessage = "Time Remaining: ", scoreMessage = "Stars: ";

//sets the player to start at left bottom left corner of the screen			initializes a variable for the peek of there jumps
float xPos = 0.0f, yPos = screenHeight - 1, jumpCieling = 0;
//sets the player as on the ground & not falling		sete not to exit the game and a star has not just been collected
bool grounded = true, jumping = false, toExit = false, starCollected = false;
//the ammont of existing fallen stars		the ammount of time the player has before the game ends		the ammount of stars the player has collected
int fallenStarAmmount = 0, countdown = COUNTDOWN_TIME, starsCollected = 0;
//a counter for the ammount of of time a player spends in the sar collected state befor returning to normal
float playerChangeBack = 0.0f;

//an array for the positions of the fallen stars
float fallenStars [maxFallenStars] [2];
//the ammount of stars currently falling
int fallingStars = 0;
//the positions of the stars currently falling
float starPositions [maxStars] [2];

//a number to convert float to int then back again
const int intToFloatConvert = 10000;
//the annount of time between star twinkles		the ammount of time a star waits in one position before moving down		the ammount of time a key needs to be down before the player moves in that direction
//		the ammount of time the player stays on one layer of elivation before rising or falling when they have jumped
const float starTwinkleDelay = 0.41f, starFallDelay = 0.082f, mySpeed = 0.041f, myJumpSpeed = 0.041f;
//seeds for random values when spawning new stars
const int starTwinkleDelayINT = (int) (starTwinkleDelay * intToFloatConvert), starFallDelayINT = (int) (starFallDelay * intToFloatConvert);
//counters for when thw stars should twinkle & move down & when the player should move left, right & up, down
float starTwinkleCount[maxStars] = {0.0f}, starFloatCount[maxStars] = {0.0f}, mySpeedCounter = 0.0f, myJumpSpeedCounter = 0.0f;

//an array of if the stars should spawn again
bool toSpawn[maxStars];


float spawnDelay[maxStars];
float spawnCounters[maxStars];



//Function to get keyboard inputs using windows GetASyncKeyState.
//The vKey parameter below is a virtual-key in Windows. there's a list of Virtual Keys that you can use here: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
bool IsKeyDown(int vKey);

//Handle our inputs from the keyboard, apply to our user variables.
void HandleInput();

//An intro sequence that writes instructions to the user and halts our program.
void IntroSequence();

void Initialize();
void Update();
void Render();

int scoreInput();

//moves the player into the air & creates a cieling, when they hit this cieling it starts to move them down untill they are ontop of the ground or a fallen star
void JumpManager ();
//checks if any new stars need to be made and if so randomly genirates a position for them
void spawnStar ();
//checks if a star are 1 unit above the ground or a falllen star 
//if true turns it into fallen stars
//if false moves it down one unit		(see starTwinkleAndFloat)
void moveStar ();
//returns true if the givven x & y peramiter match those of one of the fallen stars
bool seeFallenStars (int inX, int inY);
//prints words to the console letter by letter and incraments the buffer count accordingly
int printWord (std::string word, int rendererPos);
//manages collisions when the player is falling and moving left or right
bool airCollision (int move);
//same as printWord for numbers but converts them to strings first
int printNumber (int number, int rendererPos);
//displayes the players ending score and exits the application
void gameOver ();
//same as seeFallenStars but for falling stars
bool seeStars (int x, int y);
//makes sure stars don't spawn on-top of each other		(not sure if this works)
bool checkSpawnStarMatch (int z, int skip);
//if the player tries to move into a fallen star on the same level as them & it dosen't have a fallen star ontop of it they will move in that direction & 1 unit up
void goUpStep (float inX, float inY, int move);

int main()
{
	Initialize();

	while(true)
	{
		Update();

		if (toExit)
		{
			break;
		}

		Render();

		Sleep(FRAME_DELAY_MILLISECONDS);
	}

	scoreInput();

	return 0;
}

void Initialize()
{
	//Run the intro sequence before starting the rendering.
	IntroSequence();

	//Initialize our ConsoleRendering library with a screen width and height of 64
	ConsoleRendering::Initialize(screenWidth, screenHeight);
	srand((unsigned int) time(0));

	for (int z = 0; z < maxStars; z++)
	{
		toSpawn[z] = true;
		//spawnDelay[z] = (float) (rand() % 30);
		//spawnDelay[z] /= 60;
		spawnCounters[z] = (5 + (rand() % 25)) * 0.01f;
	}
}

void Update()
{
	//Increment the total time our program has been running.
	totalTime += FRAME_DELAY_SECONDS;
	countdown = COUNTDOWN_TIME - (int) totalTime;

	for (int z = 0; z < fallingStars; z++) {
		if ((xPos == starPositions[z][0] || xPos + 1 == starPositions[z][0] || xPos - 1 == starPositions[z][0]) && 
			(yPos == starPositions[z][1] || yPos + 1 == starPositions[z][1] || yPos - 1 == starPositions[z][1])) {
				starsCollected++;
				fallingStars--;
				toSpawn[z] = true;
				spawnDelay[z] = ((rand() % 8) * FRAME_DELAY_SECONDS) + totalTime;
				//spawnCounters[z] = (5 + (rand() % 25)) * 0.01f;
				starCollected = true;
		}
	}

	spawnStar();
	moveStar();

	HandleInput();

	if (!grounded) {
		JumpManager();
	}

	for (int y = 0; y < screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			if (x == scorePos && y == 0) {
				x = printWord(scoreMessage, x);
				x = printNumber(starsCollected, x);
			} else if (x == timePos && y == 0) {
				x = printWord(timeMessage, x);
				x = printNumber(countdown, x);
			} else if (x == xPos && y == yPos) {
				if (starCollected) {
					ConsoleRendering::DrawToScreenBuffer(x, y, '@');
				} else {
					ConsoleRendering::DrawToScreenBuffer(x, y, '^');
				}
			} else if (seeFallenStars(x, y)) {
				ConsoleRendering::DrawToScreenBuffer(x, y, '#');
			} else if (seeStars(x, y)) {
				if (starTwinkleCount[0] < starTwinkleDelay) {
					ConsoleRendering::DrawToScreenBuffer(x, y, '*');
				} else {
					ConsoleRendering::DrawToScreenBuffer(x, y, '+');
				}
			} else {
				ConsoleRendering::DrawToScreenBuffer(x, y, ' ');
			}
		}
	}

	if (totalTime >= COUNTDOWN_TIME) {
		gameOver();
	}

	if (starCollected) {
		if (playerChangeBack <= seccondsPlayerChangedFor) {
			playerChangeBack += FRAME_DELAY_SECONDS;
		} else {
			starCollected = false;
			playerChangeBack = 0;
		}
	}
}

void Render()
{
	ConsoleRendering::Render();
	ConsoleRendering::ClearScreenBuffer();
}

bool IsKeyDown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}

void HandleInput()
{
	if (IsKeyDown('D')) {
		if (xPos != screenWidth - 1 && !airCollision(1)) {
			mySpeedCounter += FRAME_DELAY_SECONDS;

			for (int z = 0; z < mySpeedCounter / mySpeed; z++) {
				xPos++;
				mySpeedCounter -= mySpeed;
			} 

			if (!seeFallenStars((int) xPos, (int) (yPos + 1)) && yPos < screenHeight - 1) {
				grounded = false;
			}
		} else if (grounded && xPos != screenWidth - 1) {
			goUpStep(xPos, yPos, +1);
		} else if (xPos == screenWidth - 1) {
			xPos = 0;
		}
	} else if (IsKeyDown('A')) {
		if (xPos != 0 && !airCollision(-1)) {
			mySpeedCounter -= FRAME_DELAY_SECONDS;

			for (int z = 0; z < (0 - mySpeedCounter) / mySpeed; z++) {
				xPos--;
				mySpeedCounter += mySpeed;
			} 

			if (!seeFallenStars((int) xPos, (int) (yPos + 1)) && yPos < screenHeight - 1) {
				grounded = false;
			}
		} else if (grounded && xPos != 0) {
			goUpStep(xPos, yPos, -1);
		} else if (xPos == 0) {
			xPos = screenWidth - 1;
		}
	}

	if (IsKeyDown(' ')) {
		if (grounded) {
			grounded = false;
			jumping = true;
			jumpCieling = yPos - jumpHeight;
		}
	}

	if (IsKeyDown('Q')) {
		toExit = true;
	}
}

void IntroSequence()
{
	std::cout << "Welcome to STAR CATCHER!\nCollect as many stars as you can in " << COUNTDOWN_TIME << " secconds!\nUse 'A' and 'D' to move and 'space' to jump.\nUse 'Q' to exit.\n";
	system("Pause");
	//clear the entire screen using system("cls") since we haven't Initialized ConsoleRendering yet.
	system("cls");
}

void JumpManager () {
	if (jumping) {
		myJumpSpeedCounter += FRAME_DELAY_SECONDS;

		for (int z = 0; z < (myJumpSpeedCounter / myJumpSpeed); z++) {
			yPos--;
			if (yPos == jumpCieling) {
				jumping = false;
				break;
			}
			myJumpSpeedCounter -= myJumpSpeed;
		}
	} else {
		myJumpSpeedCounter += FRAME_DELAY_SECONDS;

		for (int z = 0; z < (myJumpSpeedCounter / myJumpSpeed); z++) {
			yPos++;
			if ((yPos == screenHeight - 1) || (seeFallenStars((int) xPos, (int) yPos + 1))) {
				grounded = true;
				myJumpSpeedCounter = 0.0f;
				break;
			}
			myJumpSpeedCounter -= myJumpSpeed;
		}
	}
}

void spawnStar () {
	for (int z = 0; z < maxStars; z++) {

		if (toSpawn[z]) {// && spawnDelay[z] <= totalTime) {
			spawnCounters[z] -= FRAME_DELAY_SECONDS;

			//if (spawnCounters[z] <= 0) {
				int pos = 0;

				do {
					pos = rand () % (int) screenWidth;
				} while (checkSpawnStarMatch(pos, z));

				starPositions[z][0] = (float) pos;
				starPositions[z][1] = 0.0f;

				starFloatCount[z] = (float) (rand() % starFallDelayINT);
				starFloatCount[z] /= intToFloatConvert;

				starTwinkleCount[z] = (float) (rand() % starTwinkleDelayINT);
				starTwinkleCount[z] /= intToFloatConvert;

				fallingStars++;
				toSpawn[z] = false;
			//}
		}
	}
}

bool checkSpawnStarMatch (int z, int skip) {
	for (int x = 0; x < maxStars; x++ ) {
		if (z == starPositions[x][0] && x != skip) {
			return true;
		}
	}

	return false;
}

void moveStar () {
	int x = fallingStars;
	for (int z = 0; z < x; z++) {

		starFloatCount[z] += FRAME_DELAY_SECONDS;

		for (int x = 0; x < (starFloatCount[z] / starFallDelay); x++) {
			starPositions[z][1]++;
			if ((starPositions[z][1] == screenHeight - 1 || seeFallenStars((int) starPositions[z][0], (int) starPositions[z][1] + 1)) && (!toSpawn[z])) {
				fallenStars [fallenStarAmmount] [0] = starPositions [z] [0];
				fallenStars [fallenStarAmmount] [1] = starPositions [z] [1];
				fallenStarAmmount++;
				fallingStars--;
				toSpawn[z] = true;
				//spawnCounters[z] = (5 + (rand() % 25)) * 0.01f;
				spawnDelay[z] = ((rand() % 8) * FRAME_DELAY_SECONDS) + totalTime;
				starFloatCount[z] = 0.0f;
				break;
			}
			starFloatCount[z] -= starFallDelay;
		}

		if (starTwinkleCount[z] < starTwinkleDelay * 2) {
			starTwinkleCount[z] += FRAME_DELAY_SECONDS;
		} else {
			starTwinkleCount[z] = 0.0f;
		}
	}
}

bool seeFallenStars (int inX, int inY) {
	bool xMatch = false, yMatch = false;

	for (int z = 0; z < fallenStarAmmount; z++) {
		if (inX == fallenStars[z][0]) {
			xMatch = true;
		}

		if (inY == fallenStars[z][1]) {
			yMatch = true;
		}

		if (xMatch && yMatch) {
			return true;
		}
		xMatch = false;
		yMatch = false;
	}

	return false;
}

int printWord (std::string word, int rendererPos) {
	for (int z = 0; z < (signed int) word.length(); z++) {
		ConsoleRendering::DrawToScreenBuffer(rendererPos + z, 0, word[z]);
	}

	return rendererPos + word.length();
}

bool airCollision (int move) {
	bool result = false;
	if (!grounded && !jumping) {
		result = seeFallenStars((int) (xPos + move), (int) (yPos + 1));
	} else {
		result = seeFallenStars((int) (xPos + move), (int) yPos);
	}

	return result;
}

int printNumber (int number, int rendererPos) {

	std::string buffer = std::to_string(number);

	int bufferToGoTo = printWord(buffer, rendererPos);
	return bufferToGoTo;
}

void gameOver () {
	system("cls");
	std::cout << "Well done! You managed to get " << starsCollected << " stars! (^^)/*\n";

	toExit = true;
}

bool seeStars (int inX, int inY) {
	bool xMatch = false, yMatch = false;

	for (int z = 0; z < fallingStars; z++) {
		if (inX == starPositions[z][0]) {
			xMatch = true;
		}

		if (inY == starPositions[z][1]) {
			yMatch = true;
		}

		if (xMatch && yMatch) {
			return true;
		}
		xMatch = false;
		yMatch = false;
	}

	return false;
}

void goUpStep (float inX, float inY, int move) {
	bool goinUp = true;

	for (int z = 0; z < fallenStarAmmount; z++) {
		if (inX + move == fallenStars[z][0] && inY - 1 == fallenStars[z][1]) {
			goinUp = false;
		}
	}

	if (goinUp) {
		xPos += move;
		yPos--;
	}
}

int scoreInput() {
	char input = ' ';
	std::cout << "\nWould you like to save your score?\nUse Yes (y) or No (n).\n";
	while (input != 'y' && input != 'n') {
		input = _getch();
	}

	if (input == 'n') {
		return 0;
	}

	std::fstream file ("scores.txt");
	int scores[1000];
	int players = 0;
	std::string names[1000];
	std::string buffer, name;

	getline(file, buffer);
	players = std::stoi(buffer);

	for (int z = 0; z < players; z++) {
		getline(file, buffer);
		scores[z] = std::stoi(buffer);
		getline(file, names[z]);
	}

	std::cout << "\nEnter your name!\n>";
	std::getline(std::cin, name);

	names[players] = name;
	scores[players] = starsCollected;
	players++;

	for (int z = 0; z < players; z++) {
		for (int x = z + 1; x < players; x++) {
			if (scores[z] >= scores[x]) {
				int storeScore = 0;
				std::string storeName = "";
				storeScore = scores[x];
				scores[x] = scores[z];
				scores[z] = storeScore;

				storeName = names[x];
				names[x] = names[z];
				names[z] = storeName;
			}
		}
	}

	file.seekg(0, file.beg);
	file << players << "\n";

	for (int z = 0; z < players; z++) {
		file << scores[z] << "\n";
		file << names[z] << "\n";
	}

	system("cls");

	for (int z = 0; z < players; z++) {
		if (names[z] == name) {
			std::cout << ">> ";
		}
		std::cout << names[z] << ": " << scores[z] << "\n";
	}

	if (names[players - 1] == name) {
		std::cout << "NEW HIGH SCORE!!\n";
	}

	file.close();
	return 0;
}

