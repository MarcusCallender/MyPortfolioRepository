#include "Fenrir.h"

Fenrir::Fenrir(C_controler* controler) : C_fighter(controler)
{
	m_name = "Fenrir";
	m_hp = 100;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	m_pMoves[0] = new C_instantAttack(30, 0.0f, 10.0, "Midnight howl", this);
	m_pMoves[1] = new C_L_attack(15, 1.0f, 8.0, "Light jab", this);
	m_pMoves[2] = new C_H_attack(27, 2.0f, 21.0, "Heavy slash", this);
	m_pMoves[3] = new C_KD_throw(24, 3.0f, 17.0, "Grab", this);
	m_pMoves[4] = new C_block(0, 0.0f, 2.0, "Guard", this);
	m_pMoves[5] = new C_dodge(8, 0.0f, 0.2, "Dodge", this);
}

