#pragma once

#include <string>

class C_fighter;

class C_Status
{
public:
	C_Status();
	~C_Status();

	virtual std::string giveSymbol() = 0;
	virtual void effect(C_fighter* affected) = 0;
	virtual void remove() = 0;
};

class C_Toxic :public C_Status
{
public:
	C_Toxic();
	~C_Toxic();

	std::string giveSymbol();
	void effect(C_fighter* affected);
	void remove();

protected:
	int m_damage;
};

class C_Venom :public C_Status
{
public:
	C_Venom();
	~C_Venom();

	std::string giveSymbol();
	void effect(C_fighter* affected);
	void remove();

protected:
	int m_damage;
};

