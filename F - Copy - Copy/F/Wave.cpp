#include "Wave.h"

Wave::Wave(C_controler* controler) : C_fighter(controler)
{
	m_name = "Wave";
	m_hp = 90;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	m_pToxic = new C_Toxic();
	m_pVenom = new C_Venom();

	m_pMoves[0] = new C_counter(65, 0.0f, 20.0, "1000 eyes moon storm", this);
	m_pMoves[1] = new C_ToxicAttack(12, 0.8f, 9.0, "Quick jab", this, m_pToxic);
	m_pMoves[2] = new C_VenomAttack(18, 1.8f, 16.0, "Strong stab", this, m_pVenom);
	m_pMoves[3] = new C_KD_throw(20, 2.8f, 16.0, "Shove", this);
	m_pMoves[4] = new C_block(0, 0.0f, 2.0, "Guard", this);
	m_pMoves[5] = new C_dodge(8, 0.0f, 0.2, "Roll", this);
}

Wave::~Wave()
{
	C_fighter::~C_fighter();

	delete m_pToxic;
	delete m_pVenom;

	m_pToxic = nullptr;
	m_pVenom = nullptr;
}

void Wave::takeDamage(int ammount, C_fighter* vs, bool gainMeter)
{
	C_fighter::takeDamage(ammount, this, gainMeter);

	vs->removeStatus(m_pToxic);
	vs->removeStatus(m_pVenom);
}

C_VenomAttack::C_VenomAttack(int damage, float speed, double focusGain, std::string name, C_fighter * pMe, C_Status * pStatus): C_H_attack(damage, speed, focusGain, name, pMe)
{
	m_pStatus = pStatus;
}

void C_VenomAttack::win(C_fighter * vs)
{
	C_H_attack::win(vs);

	vs->giveStatus(m_pStatus);
}

C_ToxicAttack::C_ToxicAttack(int damage, float speed, double focusGain, std::string name, C_fighter * pMe, C_Status * pStatus): C_L_attack(damage, speed, focusGain, name, pMe)
{
	m_pStatus = pStatus;
}

void C_ToxicAttack::win(C_fighter * vs)
{
	C_L_attack::win(vs);

	vs->giveStatus(m_pStatus);
}
