#pragma once

#include "Fighter.h"

class Dash : public C_fighter
{
public:
	Dash(C_controler* controler);
	~Dash();

	//CHANGE
	virtual void input();
	void showOptions();

	virtual void win(C_fighter* vs);
	virtual void lose(C_fighter* vs);

protected:
	unsigned int m_luckyIndex;

	C_move* m_pLuckyMoves[m_cs_noOfMoves - 1];
};

