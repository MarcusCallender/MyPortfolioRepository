#pragma once

#include "Fighter.h"

class Lance : public C_fighter
{
public:
	Lance(C_controler* controler);

	//CHANGE
	virtual void input();
	virtual std::string status();

protected:
	virtual bool canUseHyperSkill();

	bool m_chargeReady;
};

