#pragma once

#include "Fighter.h"

class C_ModeOn : public C_move
{
public:
	C_ModeOn(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);
};

class C_ModeOff : public C_move
{
public:
	C_ModeOff(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);
};

class DSPD_017 : public C_fighter
{
public:
	DSPD_017(C_controler* controler);
	~DSPD_017();

	//CHANGE
	void input();
	void takeDamage(int ammount, C_fighter* vs, bool gainMeter = true);
	void showOptions();

	void rest();
	bool canUseHyperSkill();
	void useHyper();
	
	void misc(bool data);

protected:
	C_move* m_overloadedMoves[m_cs_noOfMoves];

	bool m_circuitesOverLoaded;
	float m_damageReduction;
};

