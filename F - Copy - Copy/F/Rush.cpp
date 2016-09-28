#include "Rush.h"

#include <string>

Rush::Rush(C_controler* controler) : C_fighter(controler)
{
	m_name = "Rush";
	m_hp = 100;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	m_pMoves[0] = new C_L_attack (30, 0.5f, 12.0, "Reverse meteor cannon",	this);
	m_pMoves[1] = new C_L_attack (15, 1.0f, 8.0,  "Light attack",			this);
	m_pMoves[2] = new C_H_attack (23, 2.0f, 13.0, "Heavy attack",			this);
	m_pMoves[3] = new C_KD_throw (25, 3.0f, 18.0, "Throw",					this);
	m_pMoves[4] = new C_parry	 (10, 0.0f, 2.0,  "Light parry",			this, L_ATTACK);
	m_pMoves[5] = new C_parry	 (20, 0.0f, 2.2,  "Heavy parry",			this, H_ATTACK);

	m_heatLevel = 0;
	m_maxHeat = 5;
}

void Rush::takeDamage(int ammount, C_fighter * vs, bool gainMeter)
{
	C_fighter::takeDamage(ammount, vs, gainMeter);

	m_heatLevel = 0;
}

void Rush::gainFocus(int ammount)
{
	//m_focus += (ammount * (1.0f * ((m_heatLevel * 2) * 0.1f)));
	m_focus += (ammount * m_heatLevel);

	if (m_focus > 100.0f)
	{
		m_focus = 100.0f;
	}
}

std::string Rush::status()
{
	std::string statString;
	statString += m_name;
	statString += ": ";
	statString += std::to_string(m_hp);

	if (m_hp != m_previousHP)
	{
		statString += "(-";
		statString += std::to_string(m_previousHP - m_hp);
		statString += ")";
	}

	statString += " (";
	statString += std::to_string(m_focus);

	if (m_focus != m_previousFocus)
	{
		statString += "(+";
		statString += std::to_string(m_focus - m_previousFocus);
		statString += ")";
	}

	statString += "/100)";
	statString += " (heat: ";
	statString += std::to_string(m_heatLevel);
	statString += ")";

	for (int z = 0; z < m_pStatuses.size(); z++)
	{
		statString += m_pStatuses[z]->giveSymbol();
	}

	if (m_knockedDown)
	{
		statString += " KD";
	}

	return statString;
}

void Rush::win(C_fighter * vs)
{
	if (m_heatLevel < m_maxHeat)
	{
		m_heatLevel++;
	}

	C_fighter::win(vs);
}

