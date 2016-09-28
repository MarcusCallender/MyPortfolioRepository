#include "DSPD_017.h"

C_ModeOn::C_ModeOn(int damage, float speed, double focusGain, std::string name, C_fighter * pMe) : C_move(damage, speed, focusGain, name, pMe)
{
	m_type = BLOCK;
}

eResult C_ModeOn::use(C_fighter * vs)
{
	if ((vs->getMove()->getType() == BLOCK) || (vs->getMove()->getType() == DODGE))
	{
		std::cout << m_name << " overloaded while " << vs->getName() << " was defending.\n";
		return SP_WIN;
	}
	else
	{
		std::cout << m_name << " coulden't overloaded as " << vs->getName() << " attacked them.\n";
		return SP_LOSE;
	}

	return SP_LOSE;
}

void C_ModeOn::win(C_fighter * vs)
{
	m_pMe->misc(true);
}

void C_ModeOn::lose(C_fighter * vs)
{
}

C_ModeOff::C_ModeOff(int damage, float speed, double focusGain, std::string name, C_fighter * pMe) : C_move(damage, speed, focusGain, name, pMe)
{
	m_type = BLOCK;
}

eResult C_ModeOff::use(C_fighter * vs)
{
	if ((vs->getMove()->getType() == BLOCK) || (vs->getMove()->getType() == DODGE))
	{
		std::cout << m_name << " vented while " << vs->getName() << " was defending.\n";
		return SP_WIN;
	}
	else
	{
		std::cout << m_name << " vented and got hit by " << vs->getName() << ".\n";
		return SP_LOSE;
	}

	return SP_LOSE;
}

void C_ModeOff::win(C_fighter * vs)
{
	m_pMe->misc(false);
}

void C_ModeOff::lose(C_fighter * vs)
{
	m_pMe->misc(false);
}

DSPD_017::DSPD_017(C_controler* controler) : C_fighter(controler)
{
	m_name = "DSPD_017";
	m_hp = 115;
	m_circuitesOverLoaded = false;
	m_damageReduction = 0.66f;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	m_pMoves[0] = new C_ModeOn(0, 1.5f, 0.0, "Overload circuits", this);
	m_pMoves[1] = new C_L_attack(13, 1.0f, 7.0, "Light hit", this);
	m_pMoves[2] = new C_H_attack(18, 2.0f, 15.0, "Heavy hit", this);
	m_pMoves[3] = new C_KD_throw(19, 3.0f, 15.0, "Suplex", this);
	m_pMoves[4] = new C_block(0, 0.0f, 2.0, "Defend", this);
	m_pMoves[5] = new C_dodge(5, 0.0f, 0.5, "Evade", this);

	m_overloadedMoves[0] = new C_ModeOff(0, 1.5f, 0.0, "Vent circuits", this);
	m_overloadedMoves[1] = new C_L_attack(18, 1.0f, 0.0, "Light hit", this);
	m_overloadedMoves[2] = new C_KD_H_attack(25, 2.0f, 0.0, "Heavy hit", this);
	m_overloadedMoves[3] = new C_KD_throw(23, 3.0f, 0.0, "Suplex", this);
	m_overloadedMoves[4] = new C_block(0, 0.0f, 2.0, "Defend", this);
	m_overloadedMoves[5] = new C_dodge(8, 0.0f, 0.0, "Evade", this);
}

DSPD_017::~DSPD_017()
{
	C_fighter::~C_fighter();

	for (int z = 0; z < 6; z++)
	{
		delete m_overloadedMoves[z];
		m_overloadedMoves[z] = nullptr;
	}
}

void DSPD_017::input()
{
	//CHANGE

	//bool toReturn = true;

	if (m_circuitesOverLoaded && (m_focus == 0))
	{
		m_pCurrentMove = m_overloadedMoves[0];
	}
	else {
		if (m_circuitesOverLoaded)
		{
			m_pControler->input(m_overloadedMoves);

			if (m_pCurrentMove == m_overloadedMoves[0])
			{
				useHyper();
			}
		}
		else {
			m_pControler->input(m_pMoves);

			if (m_pCurrentMove == m_pMoves[0])
			{
				useHyper();
			}
		}
	}

	//return toReturn;
}

void DSPD_017::takeDamage(int ammount, C_fighter * vs, bool gainMeter)
{
	if (m_circuitesOverLoaded)
	{
		m_hp -= (int) (ammount * m_damageReduction);
	}
	else {
		m_hp -= ammount;

		if (gainMeter)
		{
			gainFocus((int)(ammount * 0.2f));
		}
	}
}

void DSPD_017::showOptions()
{
	if (m_circuitesOverLoaded)
	{
		std::cout << m_name << ":\n";

		for (int z = 0; z < C_fighter::getNoOfMoves(); z++)
		{
			std::cout << m_inputs[z] << ": " << m_overloadedMoves[z]->getInfo() << "\n";
		}
	}
	else
	{
		std::cout << m_name << ":\n";

		for (int z = 0; z < C_fighter::getNoOfMoves(); z++)
		{
			std::cout << m_inputs[z] << ": " << m_pMoves[z]->getInfo() << "\n";
		}
	}
}

void DSPD_017::rest()
{
	C_fighter::rest();

	if (m_circuitesOverLoaded)
	{
		takeFocusDamage(20);
	}
}

bool DSPD_017::canUseHyperSkill()
{
	if (m_circuitesOverLoaded)
	{
		return true;
	}
	else
	{
		if (m_focus > 20)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

void DSPD_017::useHyper()
{

}

void DSPD_017::misc(bool data)
{
	m_circuitesOverLoaded = data;
}

