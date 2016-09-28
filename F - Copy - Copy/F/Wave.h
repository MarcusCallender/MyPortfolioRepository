#pragma once

#include "Fighter.h"

class C_ToxicAttack : public C_L_attack
{
public:
	C_ToxicAttack(int damage, float speed, double focusGain, std::string name, C_fighter* pMe, C_Status* pStatus);

protected:
	void	win(C_fighter* vs);

	C_Status* m_pStatus;
};

class C_VenomAttack : public C_H_attack
{
public:
	C_VenomAttack(int damage, float speed, double focusGain, std::string name, C_fighter* pMe, C_Status* pStatus);

protected:
	void	win(C_fighter* vs);

	C_Status* m_pStatus;
};

class Wave : public C_fighter
{
public:
	Wave(C_controler* controler);
	~Wave();

	void takeDamage(int ammount, C_fighter* vs, bool gainMeter = true);

protected:
	C_Status* m_pToxic;
	C_Status* m_pVenom;
};

