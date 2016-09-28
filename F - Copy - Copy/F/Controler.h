#pragma once

//#include "Fighter.h"

#include "Move.h"

class C_fighter;
class C_move;

class C_controler
{
public:
	C_controler();

	virtual void input(C_move** moves) = 0;
	virtual void result(eResult res, C_fighter* vs);
	void setFighter(C_fighter* player);
	virtual void receveResult(eAI_Result res, eAI_Type type);

protected:
	C_fighter* m_pPlayer;
};

