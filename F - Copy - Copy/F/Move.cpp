#include "Move.h"

#include "Fighter.h"

#include <string>

C_move::C_move()
{
	m_damage = 50;
	m_FocusGain = 20;
	m_name = "Riseing Tackle";
	m_speed = 1.0f;
	m_type = H_ATTACK;
}

C_move::C_move(int damage, float speed, double focusGain, std::string name, C_fighter* pMe)
{
	m_damage = damage;
	m_speed = speed;
	m_FocusGain = focusGain;
	m_name = name;
	m_pMe = pMe;
}

std::string  C_move::getInfo()
{
	return m_name;
}

int C_move::getDamage()
{
	return m_damage;
}

float C_move::getSpeed()
{
	if (m_pMe->getKnockedDown())
	{
		return m_speed + 1.0f;
	}

	return m_speed;
}

eType C_move::getType()
{
	return m_type;
}

C_L_attack::C_L_attack(int damage, float speed, double focusGain, std::string name, C_fighter* pMe) : C_move(damage, speed, focusGain, name, pMe)
{
	m_type = L_ATTACK;
}

eResult C_L_attack::use(C_fighter * vs)
{
	if (vs->getMove()->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " hit " << vs->getName() << "!\n";
		return WIN;
	}
	else if (vs->getMove()->getType() == BLOCK || vs->getMove()->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << "'s move colden't hit " << vs->getName() << ".\n";
		return LOSE;
	}
	else if (vs->getMove()->getType() == L_ATTACK || vs->getMove()->getType() == H_ATTACK)
	{
		if (vs->getMove()->getSpeed() < getSpeed())
		{
			std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
			return LOSE;
		}
		else if (vs->getMove()->getSpeed() >= getSpeed())
		{
			std::cout << m_pMe->getName() << " hit " << vs->getName() << ".\n";
			return WIN;
		}
	}

	return LOSE;
}

void C_L_attack::win(C_fighter* vs)
{
	vs->takeDamage(m_damage, m_pMe);
	m_pMe->gainFocus((int)m_FocusGain);
}

void C_L_attack::lose(C_fighter * vs)
{
}

C_H_attack::C_H_attack(int damage, float speed, double focusGain, std::string name, C_fighter* pMe) : C_move(damage, speed, focusGain, name, pMe)
{
	m_type = H_ATTACK;
}

eResult C_H_attack::use(C_fighter * vs)
{
	if (vs->getMove()->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " hit " << vs->getName() << "!\n";
		return WIN;
	}
	else if (vs->getMove()->getType() == BLOCK || vs->getMove()->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << "'s move colden't hit " << vs->getName() << ".\n";
		return LOSE;
	}
	else if (vs->getMove()->getType() == L_ATTACK || vs->getMove()->getType() == H_ATTACK)
	{
		if (vs->getMove()->getSpeed() < getSpeed())
		{
			std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
			return LOSE;
		}
		else if (vs->getMove()->getSpeed() >= getSpeed())
		{
			std::cout << m_pMe->getName() << " hit " << vs->getName() << ".\n";
			return WIN;
		}
	}

	return LOSE;
}

void C_H_attack::win(C_fighter* vs)
{
	vs->takeDamage(m_damage, m_pMe);
	m_pMe->gainFocus((int)m_FocusGain);
}

void C_H_attack::lose(C_fighter * vs)
{
}

C_throw::C_throw(int damage, float speed, double focusGain, std::string name, C_fighter* pMe) : C_move(damage, speed, focusGain, name, pMe)
{
	m_type = THROW;
}

eResult C_throw::use(C_fighter * vs)
{
	if (vs->getMove()->getType() == BLOCK || vs->getMove()->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " threw " << vs->getName() << " through there defence!\n";
		return WIN;
	}
	else if (vs->getMove()->getType() == L_ATTACK || vs->getMove()->getType() == H_ATTACK)
	{
		std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
		return LOSE;
	}
	else if (vs->getMove()->getType() == THROW)
	{
		if (vs->getMove()->getSpeed() <= getSpeed())
		{
			std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
			return LOSE;
		}
		else if (vs->getMove()->getSpeed() > getSpeed())
		{
			std::cout << m_pMe->getName() << " threw " << vs->getName() << " before they could act.\n";
			return WIN;
		}
	}

	return LOSE;
}

void C_throw::win(C_fighter* vs)
{
	vs->takeDamage(m_damage, m_pMe);
	m_pMe->gainFocus((int)m_FocusGain);
}

void C_throw::lose(C_fighter * vs)
{
}

C_block::C_block()
{
	m_type = BLOCK;
}

C_block::C_block(int damage, float speed, double focusGain, std::string name, C_fighter* pMe) : C_move(damage, speed, focusGain, name, pMe)
{
	m_type = BLOCK;
}

eResult C_block::use(C_fighter * vs)
{
	if (vs->getMove()->getType() == L_ATTACK || vs->getMove()->getType() == H_ATTACK)
	{
		std::cout << m_pMe->getName() << " blocked " << vs->getName() << "'s attack!\n";
		return WIN;
	}
	else if (vs->getMove()->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " got thrown by " << vs->getName() << ".\n";
		return LOSE;
	}
	else if (vs->getMove()->getType() == BLOCK || vs->getMove()->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " prepared for an attack from " << vs->getName() << ".\n";
		return LOSE;
	}

	return LOSE;
}

void C_block::win(C_fighter* vs)
{
	m_pMe->gainFocus((int)(vs->getMove()->getDamage() * m_FocusGain));
}

void C_block::lose(C_fighter * vs)
{
}

C_dodge::C_dodge(int damage, float speed, double focusGain, std::string name, C_fighter* pMe) : C_move(damage, speed, focusGain, name, pMe)
{
	m_type = DODGE;
}

eResult C_dodge::use(C_fighter * vs)
{
	if (vs->getMove()->getType() == L_ATTACK || vs->getMove()->getType() == H_ATTACK)
	{
		std::cout << m_pMe->getName() << " dodged " << vs->getName() << "'s attack, then countered!\n";
		return WIN;
	}
	else if (vs->getMove()->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " got thrown by " << vs->getName() << ".\n";
		return LOSE;
	}
	else if (vs->getMove()->getType() == BLOCK || vs->getMove()->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " prepared for an attack from " << vs->getName() << ".\n";
		return LOSE;
	}

	return LOSE;
}

void C_dodge::win(C_fighter * vs)
{
	vs->takeDamage(m_damage, m_pMe);
	m_pMe->gainFocus((int)m_FocusGain);
}

void C_dodge::lose(C_fighter * vs)
{
}

C_parry::C_parry(int damage, float speed, double focusGain, std::string name, C_fighter* pMe, eType parries) : C_move(damage, speed, focusGain, name, pMe)
{
	m_beats = parries;
	m_type = BLOCK;
}

eResult C_parry::use(C_fighter * vs)
{
	if ((vs->getMove()->getType() == L_ATTACK) || (vs->getMove()->getType() == H_ATTACK))
	{
		if (vs->getMove()->getType() == m_beats)
		{
			std::cout << m_pMe->getName() << " parried " << vs->getName() << "'s attack, then retaliated with a counter attack.\n";
			//win(vs);
			return WIN;
		}
		else
		{
			std::cout << m_pMe->getName() << " miss timed there parry againsed " << vs->getName() << "'s attack.\n";
			//lose(vs);
			return SP_LOSE;
		}
	}
	else if (vs->getMove()->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " got thrown by " << vs->getName() << ".\n";
		//lose(vs);
		return LOSE;
	}
	else if ((vs->getMove()->getType() == BLOCK) || (vs->getMove()->getType() == DODGE))
	{
		std::cout << m_pMe->getName() << " prepared for an attack from " << vs->getName() << ".\n";
		//lose(vs);
		return LOSE;
	}

	//lose(vs);
	return LOSE;
}

void C_parry::win(C_fighter * vs)
{
	m_pMe->gainFocus((int)(vs->getMove()->getDamage() * m_FocusGain));
	vs->takeDamage(m_damage, m_pMe);
}

void C_parry::lose(C_fighter * vs)
{
}

C_instantAttack::C_instantAttack(int damage, float speed, double focusGain, std::string name, C_fighter * pMe) : C_H_attack(damage, speed, focusGain, name, pMe)
{
	m_type = H_ATTACK;
}

float C_instantAttack::getSpeed()
{
	return m_speed;
}

C_KD_throw::C_KD_throw(int damage, float speed, double focusGain, std::string name, C_fighter * pMe) :C_throw(damage, speed, focusGain, name, pMe)
{
}

void C_KD_throw::win(C_fighter * vs)
{
	C_throw::win(vs);
	vs->knockDown();
}

C_KD_instantAttack::C_KD_instantAttack(int damage, float speed, double focusGain, std::string name, C_fighter * pMe) : C_instantAttack(damage, speed, focusGain, name, pMe)
{
}

void C_KD_instantAttack::win(C_fighter* vs)
{
	C_instantAttack::win(vs);
	vs->knockDown();
}

C_KD_H_attack::C_KD_H_attack(int damage, float speed, double focusGain, std::string name, C_fighter * pMe) : C_H_attack(damage, speed, focusGain, name, pMe)
{
}

void C_KD_H_attack::win(C_fighter * vs)
{
	C_H_attack::win(vs);
	vs->knockDown();
}

C_counter::C_counter(int damage, float speed, double focusGain, std::string name, C_fighter * pMe) : C_move(damage, speed, focusGain, name, pMe)
{
	m_type = BLOCK;
}

eResult C_counter::use(C_fighter * vs)
{
	if (vs->getMove()->getType() == L_ATTACK || vs->getMove()->getType() == H_ATTACK)
	{
		std::cout << m_pMe->getName() << " blocked and counterd " << vs->getName() << "'s attack!\n";
		return SP_WIN;
	}
	else if (vs->getMove()->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " coulden't counter " << vs->getName() << "'s throw.\n";
		return LOSE;
	}
	else if (vs->getMove()->getType() == BLOCK || vs->getMove()->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " redied into a counter stance againsed " << vs->getName() << ".\n";
		return LOSE;
	}

	return LOSE;
}

void C_counter::win(C_fighter * vs)
{
	vs->takeDamage(m_damage, m_pMe);
	m_pMe->gainFocus((int)m_FocusGain);
	vs->knockDown();
}

void C_counter::lose(C_fighter * vs)
{
}

C_vampireGrab::C_vampireGrab(int damage, float speed, double focusGain, std::string name, C_fighter * pMe, int lifeSteal) : C_throw(damage, speed, focusGain, name, pMe)
{
	m_lifeSteal = lifeSteal;
}

eResult C_vampireGrab::use(C_fighter * vs)
{
	if (vs->getMove()->getType() == BLOCK || vs->getMove()->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " threw " << vs->getName() << " through there defence!\n";
		return WIN;
	}
	else if (vs->getMove()->getType() == L_ATTACK)
	{
		std::cout << m_pMe->getName() << " ploughed through " << vs->getName() << "'s act.\n";
		return WIN;
	}
	else if (vs->getMove()->getType() == H_ATTACK)
	{
		std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
		return LOSE;
	}
	else if (vs->getMove()->getType() == THROW)
	{
		if (vs->getMove()->getSpeed() <= getSpeed())
		{
			std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
			return LOSE;
		}
		else if (vs->getMove()->getSpeed() > getSpeed())
		{
			std::cout << m_pMe->getName() << " threw " << vs->getName() << " before they could act.\n";
			return WIN;
		}
	}

	return LOSE;
}

void C_vampireGrab::win(C_fighter * vs)
{
	C_throw::win(vs);
	m_pMe->gainHealth(m_lifeSteal);
	vs->knockDown();
}

void C_vampireGrab::lose(C_fighter * vs)
{
}

