#include <conio.h>
#include <time.h>

#include "Refere.h"

#include "Rush.h"
#include "Lance.h"
#include "Wave.h"
#include "DSPD_017.h"
#include "Tarja.h"
#include "Fenrir.h"
#include "Dash.h"

void printInstructions()
{
	system("cls");
	std::cout << "Attacks beat throws.\n";
	std::cout << "Throws beat defending.\n";
	std::cout << "Defending beats Attacks.\n";
	std::cout << "\nPress any key to continue\n>";
	_getch();
}

void mainMenu(bool &exit, C_controler* pControlers[2])
{
	bool repeat = false;

	do
	{
		repeat = false;

		system("cls");
		std::cout << "Welcome to HYPER FIGHTERS!!!\n\n";
		std::cout << "What would you like to do?\n";
		std::cout << "1: Play player vs player\n";
		std::cout << "2: Play player vs CPU\n";
		std::cout << "3: Watch CPU vs CPU\n";
		std::cout << "4: Read instructions\n";
		std::cout << "5: Exit\n";
		std::cout << ">";

		int choice = _getch();

		choice -= 48;

		switch (choice)
		{
		case 1:
			pControlers[0] = new C_Player();
			pControlers[1] = new C_Player();
			break;
		case 2:
			pControlers[0] = new C_Player();
			pControlers[1] = new C_AI();
			break;
		case 3:
			pControlers[0] = new C_AI();
			pControlers[1] = new C_AI();
			break;
		case 4:
			printInstructions();
			repeat = true;
			break;
		case 5:
			exit = true;
			break;
		default:
			std::cout << "\n\nPlease enter a valid option.\n";
			_getch();
			repeat = true;
			break;
		}
	} while (repeat);
}

C_fighter* charicterSelect(C_controler* pControler, int player)
{
	int choice = 0;

	system("cls");

	std::cout << "Player " << player << ", select you're fighter!\n";
	std::cout << "1: Hothead avenger,   Rush\n";
	std::cout << "2: Charming criminal, Lance\n";
	std::cout << "3: Natural killer,    Wave\n";
	std::cout << "4: Lost robot,        DSPD_0017\n";
	std::cout << "5: Savage destroyer,  Tarja\n";
	std::cout << "6: Forgotten hero,    Fenrir\n";
	std::cout << "7: Wannabe hero,      Dash\n";
	std::cout << "0: Random select\n";
	std::cout << ">";

	choice = _getch();

	choice -= 48;

	if (choice > 7 || choice < 1)
	{
		choice = (rand() % 7) + 1;
	}

	switch (choice)
	{
	case 1:
		//Rush::selectScreen();
		return new Rush(pControler);
		break;
	case 2:
		return new Lance(pControler);
		break;
	case 3:
		return new Wave(pControler);
		break;
	case 4:
		return new DSPD_017(pControler);
		break;
	case 5:
		return new Tarja(pControler);
		break;
	case 6:
		return new Fenrir(pControler);
		break;
	case 7:
		return new Dash(pControler);
		break;
	}

	//pControler->setFighter(pFighter);

	return nullptr;
}

int main()
{
	{
		C_fighter* pFighters[2];
		C_controler* pControlers[2];
		Refere* pRef;
		bool exit = false;

		srand((unsigned)time(0));

		while (!exit)
		{
			mainMenu(exit, pControlers);

			if (!exit)
			{
				system("cls");

				//charicterSelect(pFighters[0], pControlers[0], 1);
				//charicterSelect(pFighters[1], pControlers[1], 2);
				
				pFighters[0] = charicterSelect(pControlers[0], 1);
				pFighters[1] = charicterSelect(pControlers[1], 2);
				
				pControlers[0]->setFighter(pFighters[0]);
				pControlers[1]->setFighter(pFighters[1]);

				//pControlers[0] = new C_Player();
				//pControlers[1] = new C_AI();

				//pFighters[0] = new DSPD_017(pControlers[0]);
				//pFighters[1] = new Wave(pControlers[1]);

				pRef = new Refere(pFighters[0], pFighters[1]);

				pRef->start();

				delete pRef;
				pRef = nullptr;

				//delete m_pFighters[0];
				//delete m_pFighters[1];
				//delete m_pControlers[0];
				//delete m_pControlers[1];
			}
		}
	}

	_CrtDumpMemoryLeaks();

	return 0;
}

