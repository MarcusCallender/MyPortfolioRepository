#include "Dash.h"

#include <string>

Dash::Dash(C_controler* controler) : C_fighter(controler)
{
	m_name = "Dash";
	m_hp = 95;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	m_luckyIndex = 0;

	m_pMoves[0] = new C_throw(80, 2.2f, 10.0, "Ultimate dynamic finish", this);
	m_pMoves[1] = new C_L_attack(14, 1.0f, 5.0, "Quick kick", this);
	m_pMoves[2] = new C_KD_H_attack(20, 2.0f, 15.0, "Strong punch", this);
	m_pMoves[3] = new C_throw(14, 3.0f, 20.0, "Hurl", this);
	m_pMoves[4] = new C_block(0, 0.0f, 2.0, "Block", this);
	m_pMoves[5] = new C_parry(9, 0.0f, 2.0, "Light parry", this, L_ATTACK);

	m_pLuckyMoves[0] = nullptr;
	m_pLuckyMoves[1] = new C_L_attack(21, 1.0f, 8.0, "Quick kick", this);
	m_pLuckyMoves[2] = new C_KD_H_attack(30, 2.0f, 23.0, "Strong punch", this);
	m_pLuckyMoves[3] = new C_throw(21, 3.0f, 30.0, "Hurl", this);
	m_pLuckyMoves[4] = new C_block(0, 0.0f, 3.0, "Block", this);
	m_pLuckyMoves[5] = new C_parry(14, 0.0f, 3.0, "Light parry", this, L_ATTACK);
}

Dash::~Dash()
{
	C_fighter::~C_fighter();

	for (int z = 1; z < 6; z++)
	{
		delete m_pLuckyMoves[z];
		m_pLuckyMoves[z] = nullptr;
	}
}

//CHANGE
void Dash::input()
{
	//bool returned = C_fighter::input();

	if ((m_luckyIndex != 0) && (m_pCurrentMove == m_pMoves[m_luckyIndex]))
	{
		m_pCurrentMove = m_pLuckyMoves[m_luckyIndex];
	}

	//return returned;
}

void Dash::showOptions()
{
	std::cout << m_name << ":\n";

	for (int z = 0; z < C_fighter::getNoOfMoves(); z++)
	{
		if ((z == m_luckyIndex) && (z != 0))
		{
			std::cout << m_inputs[z] << ": >> " << m_pMoves[z]->getInfo() << " <<\n";
		}
		else
		{
			std::cout << m_inputs[z] << ": " << m_pMoves[z]->getInfo() << "\n";
		}
	}
}

void Dash::win(C_fighter * vs)
{
	C_fighter::win(vs);

	m_luckyIndex = 0;
}

void Dash::lose(C_fighter * vs)
{
	C_fighter::lose(vs);

	m_luckyIndex = ((rand() % (m_cs_noOfMoves - 1)) + 1);
}

