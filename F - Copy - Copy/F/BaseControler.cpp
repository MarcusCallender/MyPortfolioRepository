#include "BaseControler.h"

C_BaseControler::C_BaseControler()
{
	m_inputs[0] = '0';
	m_inputs[1] = '1';
	m_inputs[2] = '2';
	m_inputs[3] = '3';
	m_inputs[4] = '4';
	m_inputs[5] = '5';
}

C_BaseControler::~C_BaseControler()
{
}

char C_BaseControler::getInput(int z)
{
	return m_inputs[z];
}

int C_BaseControler::findInputID(char input)
{
	for (int z = 0; z < m_cs_noOfMoves; z++)
	{
		if (input == m_inputs[z])
		{
			return z;
		}
	}

	return -1;
}

//void C_BaseControler::receveResult(eResult res, C_fighter * vs)
//{
//
//}

