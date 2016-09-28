#include "Lance.h"
#include <string>

Lance::Lance(C_controler* controler) : C_fighter(controler)
{
	m_name = "Lance";
	m_hp = 110;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	m_pMoves[0] = new C_KD_instantAttack(50, 0.0f, 20.0, "Blinding cannon", this);
	m_pMoves[1] = new C_L_attack(18, 1.0f, 6.0, "Weak punch", this);
	m_pMoves[2] = new C_H_attack(23, 2.0f, 15.0, "Strong kick", this);
	m_pMoves[3] = new C_KD_throw(27, 3.0f, 13.0, "Grab", this);
	m_pMoves[4] = new C_block(0.0f, 0.0f, 2.0, "Block", this);
	m_pMoves[5] = new C_dodge(7.0f, 0.0f, 0.2, "Evade", this);

	m_pCurrentMove = m_pMoves[5];

	m_chargeReady = false;
}

//CHANGE
void Lance::input()
{
	//bool returned = C_fighter::input();
	C_fighter::input();

	if (m_pCurrentMove->getType() == BLOCK)
	{
		m_chargeReady = true;
	}
	else
	{
		m_chargeReady = false;
	}

	//return returned;
}

std::string Lance::status()
{
	std::string statString;
	statString += m_name;
	statString += ": ";
	statString += std::to_string(m_hp);

	if (m_hp != m_previousHP)
	{
		statString += "(- ";
		statString += std::to_string(m_previousHP - m_hp);
		statString += ")";
	}

	statString += " (";
	statString += std::to_string(m_focus);

	if (m_focus != m_previousFocus)
	{
		statString += "(+ ";
		statString += std::to_string(m_focus - m_previousFocus);
		statString += ")";
	}

	statString += "/100)";

	for (int z = 0; z < m_pStatuses.size(); z++)
	{
		statString += m_pStatuses[z]->giveSymbol();
	}
	
	if (m_chargeReady)
	{
		statString += " (charged)";
	}
	else
	{
		statString += " (uncharged)";
	}

	if (m_knockedDown)
	{
		statString += " KD";
	}

	return statString;
}

bool Lance::canUseHyperSkill()
{
	if ((m_focus == 100) && m_chargeReady)
	{
		return true;
	}

	return false;
}

