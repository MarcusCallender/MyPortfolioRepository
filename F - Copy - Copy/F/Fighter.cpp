#include "Fighter.h"

#include <string>
#include <conio.h>

C_fighter::C_fighter(C_controler* controler)
{
	m_knockedDown = false;
	m_focus = 0;
	m_pCurrentMove = nullptr;

	//const std::string selectScreenText = "Test.\n";
	
	m_inputs[0] = '0';
	m_inputs[1] = '1';
	m_inputs[2] = '2';
	m_inputs[3] = '3';
	m_inputs[4] = '4';
	m_inputs[5] = '5';

	m_pControler = controler;
}

C_fighter::~C_fighter()
{
	for (int z = 0; z < m_cs_noOfMoves; z++)
	{
		if (m_pMoves[z])
		{
			delete m_pMoves[z];
			m_pMoves[z] = nullptr;
		}
	}

	delete m_pControler;
	m_pControler = nullptr;
}

std::string C_fighter::status()
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

	if (m_knockedDown)
	{
		statString += " KD";
	}

	return statString;
}

eResult C_fighter::use(C_fighter* vs)
{
	return m_pCurrentMove->use(vs);
}

void C_fighter::win(C_fighter* vs)
{
	m_pCurrentMove->win(vs);

	m_pControler->result(WIN, vs);
}

void C_fighter::lose(C_fighter* vs)
{
	m_pCurrentMove->lose(vs);

	m_pControler->result(LOSE, vs);
}

void C_fighter::giveResult(eAI_Result res, eType type)
{
	eAI_Type convertedType = AI_TYPE_NULL;

	if (type == L_ATTACK || type == H_ATTACK)
	{
		convertedType = AI_ATTACK;
	}
	else if (type == BLOCK || type == DODGE)
	{
		convertedType = AI_BLOCK;
	}
	else if (type == THROW)
	{
		convertedType = AI_THROW;
	}

	m_pControler->receveResult(res, convertedType);
}

void C_fighter::misc(bool data)
{
}

