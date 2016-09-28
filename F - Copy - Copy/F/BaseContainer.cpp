#include "BaseContainer.h"

C_BaseContainer::C_BaseContainer()
{
}

C_BaseContainer::~C_BaseContainer()
{
}

C_move * C_BaseContainer::getCurrentMove()
{
	return m_pCurrentMove;
}

const int C_BaseContainer::getNoOfMoves()
{
	return m_cs_noOfMoves;
}

void C_BaseContainer::giveStatus(C_Status * pStatus)
{
	bool alreadyGot = false;

	for (int z = 0; z < m_cs_maxStatuses; z++)
	{
		if (m_pStatuses[z] == pStatus)
		{
			alreadyGot = true;
		}
	}

	if (!alreadyGot)
	{
		for (int z = 0; z < m_cs_maxStatuses; z++)
		{
			if (m_pStatuses[z] == nullptr)
			{
				m_pStatuses[z] = pStatus;
				break;
			}
		}
	}
}

void C_BaseContainer::removeStatus(C_Status * pStatus)
{
	for (int z = 0; z < m_cs_maxStatuses; z++)
	{
		if (m_pStatuses[z] == pStatus)
		{
			m_pStatuses[z] = nullptr;
		}
	}
}

void C_BaseContainer::showOptions()
{
	std::cout << m_pFighter->getName() << ":\n";

	for (int z = 0; z < m_cs_noOfMoves; z++)
	{
		std::cout << m_pControler->getInput[z] << ": " << m_pMoves[z]->getInfo() << "\n";
	}
}

void C_BaseContainer::showInput()
{
	std::cout << m_pFighter->getName() << " used " << m_pCurrentMove->getInfo() << ".\n";
}

void C_BaseContainer::input()
{
	m_pCurrentMove = m_pControler->input(m_pMoves);

	if (m_pCurrentMove == m_pMoves[0])
	{
		m_pFighter->useHyper();
	}
}

//eResult C_BaseContainer::use()
//{
//	return m_pCurrentMove->use();
//}

void C_BaseContainer::rest()
{
	m_pFighter->rest();

	for (int z = 0; z < m_cs_maxStatuses; z++)
	{
		if (m_pStatuses[z] != nullptr) {
			//m_pStatuses[z]->effect();
		}
	}
}

