#include "Tarja.h"

Tarja::Tarja(C_controler* controler) : C_fighter(controler)
{
	m_name = "Tarja";
	m_hp = 105;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	m_pMoves[0] = new C_vampireGrab(30, 1.5f, 15.0, "Savage tornado", this, 15);
	m_pMoves[1] = new C_L_attack(18, 1.2f, 6.0, "Weak jab", this);
	m_pMoves[2] = new C_KD_H_attack(24, 2.2f, 13.0, "Heavy rush", this);
	m_pMoves[3] = new C_KD_throw(26, 3.2f, 14.0, "Grasp", this);
	m_pMoves[4] = new C_block(0, 0.2f, 2.0, "Defend", this);
	m_pMoves[5] = new C_dodge(7, 0.2f, 6.0, "Side step", this);
}

