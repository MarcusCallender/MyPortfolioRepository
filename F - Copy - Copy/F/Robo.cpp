//#include "Robo.h"
//
//Robo::Robo(C_controler* controler) : C_fighter(controler)
//{
//	m_name = "Robo";
//	m_hp = 115;
//	m_circuitesOverLoaded = false;
//
//	m_previousHP = m_hp;
//	m_previousFocus = m_focus;
//
//	m_pMoves[0] = new C_modeSwitch();
//	m_pMoves[1] = new C_L_attack(13, 1.0f, 7.0, "Light hit", this);
//	m_pMoves[2] = new C_H_attack(18, 2.0f, 15.0, "Heavy hit", this);
//	m_pMoves[3] = new C_KD_throw(19, 3.0f, 15.0, "Suplex", this);
//	m_pMoves[4] = new C_block(0, 0.0f, 2.0, "Defend", this);
//	m_pMoves[5] = new C_dodge(5, 0.0f, 0.5, "Evade", this);
//
//	m_pChargedMoves[0] = new C_modeSwitch();
//	m_pChargedMoves[1] = new C_L_attack(18, 1.0f, 0.0, "Light hit", this);
//	m_pChargedMoves[2] = new C_KD_H_attack(25, 2.0f, 0.0, "Heavy hit", this);
//	m_pChargedMoves[3] = new C_KD_throw(23, 3.0f, 0.0, "Suplex", this);
//	m_pChargedMoves[4] = new C_block(0, 0.0f, 2.0, "Defend", this);
//	m_pChargedMoves[5] = new C_dodge(8, 0.0f, 0.0, "Evade", this);
//}
//
//Robo::~Robo()
//{
//	C_fighter::~C_fighter();
//
//	for (int z = 0; z < 6; z++) {
//		delete m_pChargedMoves[z];
//		m_pChargedMoves[z] = nullptr;
//	}
//}
//
//void Robo::misc(void * data)
//{
//	m_circuitesOverLoaded = *static_cast<bool*>(data);
//}
//
//C_modeSwitch::C_modeSwitch()
//{
//}
//
//eResult C_modeSwitch::use(C_fighter * vs)
//{
//	return eResult();
//}
//
//void C_modeSwitch::win(C_fighter * vs)
//{
//	m_pMe->misc(&on);
//}
//
//void C_modeSwitch::lose(C_fighter * vs)
//{
//}
//
//C_barrier::C_barrier(int damage, float speed, double focusGain, std::string name, C_fighter * pMe, float absorbtion) : C_block(damage, speed, focusGain, name, pMe)
//{
//	m_absorbtion = absorbtion;
//}
//
//void C_barrier::win(C_fighter * vs)
//{
//	m_pMe->gainHealth(m_absorbtion * vs->getMove()->getDamage());
//}
