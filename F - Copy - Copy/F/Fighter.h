#pragma once

#include "Move.h"
#include "AI.h"
#include "Player.h"
#include "Status.h"

#include <iostream>
#include <vector>

class C_fighter
{
	friend class C_Player;
	friend class C_AI;

public:
	C_fighter(C_controler* controler);
	~C_fighter();

	//CHANGE
	eResult use(C_fighter* vs);
	virtual void win(C_fighter* vs);
	virtual void lose(C_fighter* vs);
	void giveResult(eAI_Result res, eType type);

	//static bool selectScreen();

	virtual void misc(bool data);

protected:
	//static const std::string selectScreenText;

	C_controler* m_pControler;
};

