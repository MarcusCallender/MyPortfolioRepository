#pragma once

#include "Fighter.h"
#include "Move.h"

#include <iostream>

class Rush : public C_fighter
{
public:
	Rush(C_controler* controler);

	void takeDamage(int ammount, C_fighter* vs, bool gainMeter = true);
	
	virtual void gainFocus(int ammount);
	virtual std::string status();

	virtual void win(C_fighter* vs);

protected:
	int m_heatLevel;
	int m_maxHeat;
};

