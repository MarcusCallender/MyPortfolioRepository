#include "AI.h"

#include "Move.h"

#include "Fighter.h"

#include <conio.h>

#include <fstream>

C_AI::C_AI()
{
	for (int z = 0; z < AI_TYPE_TOTAL; z++)
	{
		for (int x = 0; x < AI_RES_TOTAL; x++)
		{
			for (int c = 0; c < AI_TYPE_TOTAL; c++)
			{
				m_data[z][x][c] = 0;
			}
		}
	}

	m_previousResult = AI_RES_NULL;
	m_previousType = AI_TYPE_NULL;

	m_defaultMove = 1;
}

C_AI::~C_AI()
{
	std::fstream file("scores.txt");

	for (int z = 0; z < AI_TYPE_TOTAL; z++)
	{
		for (int x = 0; x < AI_RES_TOTAL; x++)
		{
			for (int c = 0; c < AI_TYPE_TOTAL; c++)
			{
				file << m_data[z][x][c] << "\n";
			}
		}
	}
}

void C_AI::input(C_move** moves)
{
	/*if (m_pPlayer->canUseHyperSkill())
	{
		if ((rand() % 2) > 0)
		{
			//m_pPlayer->m_pCurrentMove = m_pPlayer->m_pMoves[0];
			m_pPlayer->m_pCurrentMove = moves[0];
		}
		else
		{
			//m_pPlayer->m_pCurrentMove = m_pPlayer->m_pMoves[(rand() % 5) + 1];
			m_pPlayer->m_pCurrentMove = moves[(rand() % 5) + 1];
		}
	}
	else
	{
		//m_pPlayer->m_pCurrentMove = m_pPlayer->m_pMoves[(rand() % 5) + 1];
		m_pPlayer->m_pCurrentMove = moves[(rand() % 5) + 1];
	}*/

	int predictions = predictMoveConfidence();

	if (predictions == 3)
	{
		m_pPlayer->m_pCurrentMove = moves[m_defaultMove];
	}
	else if (predictions == 2)
	{
		eAI_Type lowest = findLowest();

		if (lowest == AI_ATTACK)
		{
			useThrow(moves);
		}
		else if (lowest == AI_BLOCK)
		{
			useAttack(moves);
		}
		else if (lowest == AI_THROW)
		{
			useBlock(moves);
		}
	}
	else if (predictions == 1)
	{
		eAI_Type highist = findHighest();

		if (highist == AI_ATTACK)
		{
			useBlock(moves);
		}
		else if (highist == AI_BLOCK)
		{
			useThrow(moves);
		}
		else if (highist == AI_THROW)
		{
			useAttack(moves);
		}
	}

	std::cout << "...Decideing.\n>";
	_getch();
}

void C_AI::result(eResult res, C_fighter * vs)
{
	m_eResults.push_back(res);
	m_moves.push_back(vs->getMove());
}

void C_AI::receveResult(eAI_Result res, eAI_Type type)
{
	if (m_previousType != AI_TYPE_NULL && m_previousResult != AI_RES_NULL)
	{
		m_data[m_previousType][m_previousResult][type]++;
	}

	m_previousResult = res;
	m_previousType = type;
}

int C_AI::predictMoveConfidence()
{
	int _attacks = m_data[m_previousType][m_previousResult][AI_ATTACK];
	int _blocks = m_data[m_previousType][m_previousResult][AI_BLOCK];
	int _throws = m_data[m_previousType][m_previousResult][AI_THROW];

	if (_attacks == _blocks && _blocks == _throws)
	{
		return 3;
	}
	else if (_attacks != _blocks && _blocks != _throws && _throws != _attacks)
	{
		return 1;
	}
	else
	{
		return 2;
	}

	return 0;
}

eAI_Type C_AI::findLowest()
{
	eAI_Type lowest = AI_ATTACK;

	for (int z = 1; z < AI_TYPE_TOTAL; z++)
	{
		if (m_data[m_previousType][m_previousResult][z] < m_data[m_previousType][m_previousResult][lowest])
		{
			lowest = (eAI_Type) z;
		}
	}

	return lowest;
}

eAI_Type C_AI::findHighest()
{
	eAI_Type highest = AI_ATTACK;

	for (int z = 1; z < AI_TYPE_TOTAL; z++)
	{
		if (m_data[m_previousType][m_previousResult][z] > m_data[m_previousType][m_previousResult][highest])
		{
			highest = (eAI_Type)z;
		}
	}

	return highest;
}

void C_AI::useAttack(C_move** moves)
{
	if (m_pPlayer->canUseHyperSkill())
	{
		if (moves[0]->getType() == L_ATTACK || moves[0]->getType() == H_ATTACK)
		{
			m_pPlayer->m_pCurrentMove = moves[0];
		}
	}
	else
	{
		m_pPlayer->m_pCurrentMove = moves[(rand() % 2) + 1];
	}
}

void C_AI::useBlock(C_move** moves)
{
	if (m_pPlayer->canUseHyperSkill())
	{
		if (moves[0]->getType() == BLOCK || moves[0]->getType() == DODGE)
		{
			m_pPlayer->m_pCurrentMove = moves[0];
		}
	}
	else
	{
		m_pPlayer->m_pCurrentMove = moves[(rand() % 2) + 4];
	}
}

void C_AI::useThrow(C_move** moves)
{
	if (m_pPlayer->canUseHyperSkill())
	{
		if (moves[0]->getType() == THROW)
		{
			m_pPlayer->m_pCurrentMove = moves[0];
		}
	}
	else
	{
		m_pPlayer->m_pCurrentMove = moves[3];
	}
}

