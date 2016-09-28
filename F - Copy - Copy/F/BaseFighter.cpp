#include "BaseFighter.h"

#include <iostream>

C_BaseFighter::C_BaseFighter()
{
}

C_BaseFighter::~C_BaseFighter()
{
}

bool C_BaseFighter::isKOd()
{
	if (m_hp <= 0)
	{
		return true;
	}

	return false;
}

void C_BaseFighter::knockDown()
{
	m_knockedDown = true;
	std::cout << m_name << " got knocked down.\n";
}

void C_BaseFighter::gainHp(int ammount)
{
	m_hp += ammount;
}

void C_BaseFighter::rest()
{
	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	m_knockedDown = false;
}

int C_BaseFighter::getHp()
{
	return m_hp;
}

void C_BaseFighter::takeDamage(int ammount, bool gainMeter)
{
	m_hp -= ammount;

	if (gainMeter)
	{
		gainFocus((int)(ammount * 0.2f));
	}
}

std::string C_BaseFighter::getName()
{
	return m_name;
}

bool C_BaseFighter::canUseHyperSkill()
{
	if (m_focus == 100)
	{
		return true;
	}

	return false;
}

void C_BaseFighter::addToName(std::string add)
{
	m_name += add;
}

bool C_BaseFighter::getKnockedDown()
{
	return m_knockedDown;
}

void C_BaseFighter::useHyper()
{
	m_focus = 0;
}

void C_BaseFighter::takeFocusDamage(int ammount)
{
	m_focus -= ammount;

	if (m_focus < 0)
	{
		m_focus = 0;
	}
}

void C_BaseFighter::gainFocus(int ammount)
{
	m_focus += ammount;

	if (m_focus > m_maxFocus)
	{
		m_focus = m_maxFocus;
	}
}
