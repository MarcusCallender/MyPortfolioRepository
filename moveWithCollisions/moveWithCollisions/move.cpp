#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <time.h>

const int rockAmmount = 9;
const int displayWhidth = 80, gridHeight = 20;
int mePosX = 0, mePosY = 0, mePosT = 0, exPosX = 1, exPosY = 0, exPosT = 0, exPosT2 = 0;
int enemyPosX = 0, enemyPosY = 0, enemyPosT = 0;
int rockPos[rockAmmount], rockCollision[rockAmmount];
int keyPos[3], keyColl[3];
bool kGot = false, eGot = false, yGot = false;
char input = ' ';
bool clash = false;
int win = 0;
int turns = 0;
int enemyShell = 0;

int totalPosition (int x, int y) {
	int t = 0;
	t = ((x * 2) + 1) + (y * displayWhidth);
	return t;
}

bool checkMatch (int c, int list[rockAmmount]) {

	for (int z = 0; z < rockAmmount; z++) {
		if (list[z] == c) {
			return true;
		}
	}

	return false;
}

char view (int z) {
	if ((z == mePosT && z == enemyPosT) || (z - 1 == mePosT && z - 1 == enemyPosT)) {
				return 'X';

			} else if (z % displayWhidth == 0 || z % displayWhidth - 79 == 0) {
				return '#';

			} else if (z == mePosT || z == mePosT + 1) {
				return '^';

			} else if ( z == enemyPosT) {
				return '}';

			} else if (z == enemyPosT + 1) {
				return '{';
			}
			
			else if (z == exPosT || z == exPosT + 1 || z == exPosT2 || z == exPosT2 + 1) {
				if (kGot && eGot && yGot) {
					return '|';
				} else {
					return '-';
				}

			} else if (!kGot && z == keyPos[0]) {
				return 'K';
			} else if (!eGot && z == keyPos[1]) {
				return 'E';
			} else if (!yGot && z == keyPos[2]) {
				return 'Y';

			} else if (checkMatch(z, rockPos)) {
				return '%';

			} else if (z == enemyShell || z == enemyShell + 1) {
				return '$';
				z++;
			} else {
				return ' ';

			}
}

void debug (int me, int enemy, int rock[rockAmmount], int exit1, int exit2, int key[3]) {
	std::cout << "Me pos: " << me << "\n";

	std::cout << "Enemy pos: " << enemy << "\n";

	for (int z = 0; z < rockAmmount; z++) {
		std::cout << "Rock " << z << ": " << rock[z] << "\n";
	}

	std::cout << "exit 1 pos: " << exit1 << "\n";
	std::cout << "exit 2 pos: " << exit2 << "\n";


	std::cout << "K pos: " << key[0] << "\n";
	std::cout << "E pos: " << key[1] << "\n";
	std::cout << "Y pos: " << key[2] << "\n";

}

bool collisionMatch (int x, int y, int c, int list[rockAmmount]) {

	int t = 0;
	switch (c) {
	case 0 : x++;
	case 1 : x--;
	case 2 : y++;
	case 3 : y--;
	}

	t = ((x * 2) + 1) + (y * displayWhidth);

	//std::cout << "Bug\n";

	for (int z = 0; z < rockAmmount; z++) {
		if (list[z] == t) {
			return true;
		}
	}

	return false;
}

int main () {
	//define & initialize variables
	std::string display = "";

	//randomize exit position
	srand(time(0));
	exPosX = rand() % 19;
	exPosX += 19;
	exPosY = rand() % 10;
	exPosY += 9;

	do {
		clash = false;
		enemyPosX = rand() % 19;
		enemyPosX += 19;
		enemyPosY = rand() % 10;
		enemyPosY += 9;

		if ((enemyPosY == exPosY) || (enemyPosY == (exPosY + 1))) {
			if (enemyPosX == exPosX || enemyPosX == (exPosX + 1) || enemyPosX == (exPosX - 1)) {
				clash = true;
			}
		}
	} while (clash);

	//set the exit position
	exPosT = totalPosition(exPosX, exPosY);
	exPosT2 = exPosT + displayWhidth;
	enemyPosT = totalPosition(enemyPosX, enemyPosY);

	for (int z = 0; z < rockAmmount; z++) {
		bool clash = false;

		rockPos[z] = rand() % (displayWhidth * gridHeight);

		//if (z % displayWhidth == 0 || z % displayWhidth - 79 == 0) {
		//clash = true;
		//std::cout << "Yes\n";
		//}		breaks the code

		if (rockPos[z] == mePosT || rockPos[z] == exPosT || rockPos[z] == exPosT2 || rockPos[z] == enemyPosT) {
			clash = true;
		}

		for (int x = 0; x < z; x++) {
			if (rockPos[z] == rockPos[x]) {
				clash = true;
			}
		}

		if (clash) {
			z--;
		}
	}

	for (int z = 0; z < 3; z++) {
		bool clash = false;

		keyPos[z] = rand() % (displayWhidth * gridHeight);

		if (keyPos[z] == mePosT || keyPos[z] == exPosT || keyPos[z] == exPosT2) {
			clash = true;
		}

		if (keyPos[z] % displayWhidth == 0 || keyPos[z] % displayWhidth - 78 == 0) {
			clash = true;
		}

		for (int x = 0; x < rockAmmount; x++) {
			if (rockPos[x] == keyPos[z]) {
				clash = true;
			}
		}

		for (int x = 0; x < z; x++) {
			if (keyPos[z] == keyPos[x]) {
				clash = true;
			}
		}

		if (clash) {
			z--;
		}
	}

	for (int z = 0; z < rockAmmount; z++) {
		if (rockPos[z] % 2 == 0) {
			rockCollision[z] = rockPos[z] - 1;
		} else {
			rockCollision[z] = rockPos[z];
		}
	}

	for (int z = 0; z < 3; z++) {
		if (keyPos[z] % 2 == 0) {
			keyColl[z] = keyPos[z] - 1;
		} else {
			keyColl[z] = keyPos[z];
		}
	}

	//hides the curser using magic
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	//GAME LOOP START
	while (true) {
		system("cls");

		//display scene
		std::cout << display;
		//debug (mePosT, enemyPosT, rockPos, exPosT, exPosT2, keyPos);

		if ((mePosT == exPosT ||  mePosT == exPosT2) && (kGot && eGot && yGot)) {
			win = 1;
			break;
		}

		if (mePosT == enemyPosT) {
			win = -1;
			break;
		}

		//reset data
		display = "";

		input = _getch();

		if (input == 'd') {
			if (mePosX != 38) {
				mePosX++;
			}
		} else if (input == 'a') {
			if (mePosX != 0) {
				mePosX--;
			}
		} else if (input == 's') {
			if (mePosY != 19) {
				mePosY++;
			}
		} else if (input == 'w') {
			if (mePosY != 0) {
				mePosY--;
			}
		} else if (input == 'p') {
			break;
		}

		mePosT = totalPosition(mePosX, mePosY);

		for (int z = 0; z < rockAmmount; z++) {
			if (mePosT == rockCollision[z]) {
				if (input == 'd') {
					mePosX--;
				} else if (input == 'a') {
					mePosX++;
				} else if (input == 's') {
					mePosY--;
				} else if (input == 'w') {
					mePosY++;
				}

				mePosT = totalPosition(mePosX, mePosY);
			}
		}

		if (mePosT == keyColl[0]) {
			kGot = true;
		} else if (mePosT == keyColl[1]) {
			eGot = true;
		} else if (mePosT == keyColl[2]) {
			yGot = true;
		}

		input = ' ';

		enemyShell = enemyPosT;

		if ((turns % 3 != 0) && (enemyPosT != mePosT)) {
	bool moved = true, exception = false, doubleException = false;
	do {
		moved = true;
		int moveVertical = false;
		
		//key : 0 = x++ (right), 1 = x-- (left), 2 = y++ (down), 3 = y-- (up)
		int change = 0;

		if (mePosX != enemyPosX && mePosY != enemyPosY) {
			int dir = rand() % 2;

			if (exception && dir == 1) {
				dir = 0;
			} else if (exception && dir == 0) {
				dir = 1;
			}

			if (dir == 1) {
				moveVertical = true;
			}
			
		} else if (enemyPosX == mePosX) {
			moveVertical = true;
		}

		if (exception) {
			moveVertical = !moveVertical;
		}

		if (moveVertical) {
			if (enemyPosY > mePosY) {
				change = 3;
				
				if (collisionMatch(enemyPosX, enemyPosY, change, rockCollision)) {
					moved = false;
					
					if (exception) {
						doubleException = true;
					} else {
						exception = true;
					}
				} else {
					enemyPosY--;
				}
			} else if (enemyPosY < mePosY) {
				change = 2;
				
				if (collisionMatch(enemyPosX, enemyPosY, change, rockCollision)) {
					moved = false;
					
					if (exception) {
						doubleException = true;
					} else {
						exception = true;
					}
				} else {
					enemyPosY++;
				}
			} else if (exception) {
				if (doubleException) {
					change = 3;
				} else {
					change = 2;
				}
				
				if (collisionMatch(enemyPosX, enemyPosY, change, rockCollision)) {
					moved = false;
					
					if (exception) {
						doubleException = true;
					} else {
						exception = true;
					}
				} else {
					if (change == 3) {
						enemyPosY--;
					} else {
						enemyPosY++;
					}
				}
			}
		} else if (!moveVertical) {
			if (enemyPosX > mePosX) {
				change = 1;
				
				if (collisionMatch(enemyPosX, enemyPosY, change, rockCollision)) {
					moved = false;
					
					if (exception) {
						doubleException = true;
					} else {
						exception = true;
					}
				} else {
					enemyPosX--;
				}
			} else if (enemyPosX < mePosX) {
				change = 0;
				
				if (collisionMatch(enemyPosX, enemyPosY, change, rockCollision)) {
					moved = false;
					
					if (exception) {
						doubleException = true;
					} else {
						exception = true;
					}
				} else {
					enemyPosX++;
				}
			} else if (exception) {
				if (doubleException) {
					change = 1;
				} else {
					change = 0;
				}
				
				if (collisionMatch(enemyPosX, enemyPosY, change, rockCollision)) {
					moved = false;
					
					if (exception) {
						doubleException = true;
					} else {
						exception = true;
					}
				} else {
					if (change == 0) {
						enemyPosX--;
					} else {
						enemyPosX++;
					}
				}
			} while (!moved);
		}

		if (enemyPosY > 20 || enemyPosY < 0) {
			moved = false;
			//don't change exception
		}
				
	} while (false);
}

		enemyPosT = totalPosition(enemyPosX, enemyPosY);
		turns++;

		//modify data	(set scene)

		for (int z = 0; z < displayWhidth; z++) {
			display += "#";
		}

		for (int z = 0; z < (displayWhidth * gridHeight); z++) {
			display += view (z);
		}

		for (int z = 0; z < displayWhidth; z++) {
			display += "#";
		}

		if (kGot) {
			display += "K";
		}

		if (eGot) {
			display += "E";
		}

		if (yGot) {
			display += "Y";
		}

		if (kGot && eGot && yGot) {
			display += "!\n";
		}

		//Sleep(64);
	}

	if (win == 1) {
		std::cout << "You win!! *\\(^.^)/*\n";
	} else if (win == -1) {
		std::cout << "Sorry, you got caught.\n";
	} else {
		std::cout << "Bye!! (^^)/\n";
	}

	return 0;
}

//faster way to add 60(+) # to a string?
