#include "Refere.h"

#include <string>

Refere::Refere(C_fighter * one, C_fighter * two)
{
	m_pFighters[0] = one;
	m_pFighters[1] = two;

	if (m_pFighters[0]->getName().compare(m_pFighters[1]->getName()) == 0)
	{
		m_pFighters[0]->addToName(" 1");
		m_pFighters[1]->addToName(" 2");
	}
}

Refere::~Refere()
{
	if (m_pFighters[0])
	{
		delete m_pFighters[0];
		m_pFighters[0] = nullptr;
	}

	if (m_pFighters[1])
	{
		delete m_pFighters[1];
		m_pFighters[1] = nullptr;
	}
}

std::string Refere::UI()
{
	std::string toReturn = m_pFighters[0]->status();
	toReturn += " vs ";
	toReturn += m_pFighters[1]->status();
	toReturn += "\n";

	return toReturn;
}

void Refere::HUD()
{
	std::cout << m_pFighters[0]->status() << "   vs   " << m_pFighters[1]->status() << "\n";
}

void Refere::evaluate()
{
	m_pFighters[0]->showInput();
	m_pFighters[1]->showInput();
	std::cout << "\n";

	eResult resOne = m_pFighters[0]->use(m_pFighters[1]);
	eResult resTwo = m_pFighters[1]->use(m_pFighters[0]);

	m_pFighters[0]->rest();
	m_pFighters[1]->rest();

	if (resOne > resTwo)
	{
		m_pFighters[0]->win(m_pFighters[1]);
		m_pFighters[1]->lose(m_pFighters[0]);

		m_pFighters[0]->giveResult(AI_WIN, m_pFighters[1]->getMove()->getType());
		m_pFighters[1]->giveResult(AI_LOSE, m_pFighters[0]->getMove()->getType());
	}
	else if (resTwo > resOne)
	{
		m_pFighters[1]->win(m_pFighters[0]);
		m_pFighters[0]->lose(m_pFighters[1]);
		
		m_pFighters[0]->giveResult(AI_LOSE, m_pFighters[1]->getMove()->getType());
		m_pFighters[1]->giveResult(AI_WIN, m_pFighters[0]->getMove()->getType());
	}
	else if (resTwo == resOne)
	{
		if ((resOne == LOSE) || (resOne == SP_LOSE))
		{
			m_pFighters[0]->lose(m_pFighters[1]);
			m_pFighters[1]->lose(m_pFighters[0]);
		}
		else if ((resOne == WIN) || (resOne == SP_WIN))
		{
			m_pFighters[0]->win(m_pFighters[1]);
			m_pFighters[1]->win(m_pFighters[0]);
		}

		m_pFighters[0]->giveResult(AI_DRAW, m_pFighters[1]->getMove()->getType());
		m_pFighters[1]->giveResult(AI_DRAW, m_pFighters[0]->getMove()->getType());
	}
}

void Refere::end()
{
	system("cls");

	if (m_pFighters[0]->getHp() > 0)
	{
		std::cout << m_pFighters[0]->getName() << " wins!!\n";
	}
	else if (m_pFighters[1]->getHp() > 0)
	{
		std::cout << m_pFighters[1]->getName() << " wins!!\n";
	}
	else
	{
		std::cout << "The match was a draw.\n";
	}

	std::cout << "Press any key to continue.\n";
	system("pause");
}

void Refere::start()
{
	while (!m_pFighters[0]->isKOd() && !m_pFighters[1]->isKOd())
	{
		system("cls");

		HUD();
		m_pFighters[0]->input();

		//CHANGE
		/*
		do {
			HUD();
		} while(m_pFighters[0]->input());
		*/

		system("cls");

		HUD();
		m_pFighters[1]->input();

		system("cls");

		evaluate();

		system("pause");
		system("cls");
	}

	end();
}

