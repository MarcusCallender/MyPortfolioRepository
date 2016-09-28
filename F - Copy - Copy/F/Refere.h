#pragma once
#include "Fighter.h"

class Refere
{
public:
	Refere(C_fighter* one, C_fighter* two);
	~Refere();

	void start();

protected:
	std::string UI();
	void HUD();
	void evaluate();
	void end();

	C_fighter* m_pFighters[2];
};

