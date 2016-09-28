//#pragma once
//
//#include "Fighter.h"
//#include "Move.h"
//
//class C_modeSwitch : public C_move
//{
//public:
//	C_modeSwitch();
//
//	eResult use(C_fighter* vs);
//
//protected:
//	void win(C_fighter* vs);
//	void lose(C_fighter* vs);
//	bool on = true;
//	bool off = false;
//};
//
//class C_barrier : public C_block
//{
//public:
//	C_barrier(int damage, float speed, double focusGain, std::string name, C_fighter* pMe, float absorbtion);
//
//protected:
//	void win(C_fighter* vs);
//
//	float m_absorbtion;
//};
//
//class Robo : public C_fighter
//{
//public:
//	Robo(C_controler* controler);
//	~Robo();
//
//	virtual void misc(void* data);
//
//protected:
//	bool m_circuitesOverLoaded;
//
//	C_modeSwitch* on;
//	C_modeSwitch* off;
//
//	C_move** m_moveSet;
//
//	C_move* m_pChargedMoves[m_cs_noOfMoves];
//};
//
