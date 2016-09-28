#include "Player.h"

#include "Fighter.h"

#include <conio.h>

C_Player::C_Player()
{
}

//CHANGE
void C_Player::input(C_move** moves)
{
	char in = ' ';

	do
	{
		m_pPlayer->showOptions();

		std::cout << ">";
		in = _getch();

		system("cls");
	} while (m_pPlayer->findInputID(in) == -1);

	
	/*if (m_pPlayer->findInputID(in) == -1)
	{
		m_pPlayer->m_pCurrentMove = moves[m_pPlayer->findInputID(in)];
	}
	else {
		m_pPlayer->m_pCurrentMove = nullptr;
	}*/
	

	m_pPlayer->m_pCurrentMove = moves[m_pPlayer->findInputID(in)];
}

