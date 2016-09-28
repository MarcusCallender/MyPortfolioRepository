#ifndef __BASE_CONTROLER__
#define __BASE_CONTROLER__

#include "Move.h"

class C_BaseControler
{
public:

	C_BaseControler();
	~C_BaseControler();

	virtual C_move* input(C_move** moves) = 0;
	//virtual void result(eResult res, C_fighter* vs);
	//virtual void receveResult(eAI_Result res, eAI_Type type);

	char getInput(int z);
	int findInputID(char input);

protected:

	const static int m_cs_noOfMoves = 6;

	char m_inputs[m_cs_noOfMoves];

}

#endif // !__BASE_CONTROLER__

