#pragma once

class C_fighter;

#include <iostream>

enum eResult
{
	SP_LOSE,
	LOSE,
	WIN,
	SP_WIN
};

enum eType
{
	L_ATTACK,
	H_ATTACK,
	THROW,
	BLOCK,
	DODGE
};

enum eAI_Result
{
	AI_LOSE,
	AI_DRAW,
	AI_WIN,
	AI_RES_TOTAL,
	AI_RES_NULL
};

enum eAI_Type
{
	AI_ATTACK,
	AI_BLOCK,
	AI_THROW,
	AI_TYPE_TOTAL,
	AI_TYPE_NULL
};

class C_move
{
public:
	C_move();
	C_move(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	std::string getInfo();
	virtual eResult use(C_fighter* vs) = 0;
	virtual void win(C_fighter* vs) = 0;
	virtual void lose(C_fighter* vs) = 0;

	int	getDamage();
	virtual float getSpeed();
	eType getType();

protected:

	int m_damage;
	float m_speed;
	double m_FocusGain;
	std::string m_name;
	eType m_type;
	C_fighter* m_pMe;
};

class C_L_attack : public C_move
{
public:
	C_L_attack(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);
};

class C_H_attack : public C_move
{
public:
	C_H_attack(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);
};

class C_throw : public C_move
{
public:
	C_throw(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);
};

class C_block : public C_move
{
public:
	C_block();
	C_block(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);
};

class C_dodge : public C_move
{
public:
	C_dodge(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);
};

class C_parry : public C_move
{
public:
	C_parry(int damage, float speed, double focusGain, std::string name, C_fighter* pMe, eType parries);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);

	eType m_beats;
};

class C_KD_throw :public C_throw
{
public:
	C_KD_throw(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

protected:
	void win(C_fighter* vs);
};

class C_instantAttack : public C_H_attack
{
public:
	C_instantAttack(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	float getSpeed();
};

class C_KD_instantAttack : public C_instantAttack
{
public:
	C_KD_instantAttack(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	void win(C_fighter* vs);
};

class C_KD_H_attack : public C_H_attack
{
public:
	C_KD_H_attack(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	void win(C_fighter* vs);
};

class C_counter : public C_move
{
public:
	C_counter(int damage, float speed, double focusGain, std::string name, C_fighter* pMe);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);
};

class C_vampireGrab :public C_throw
{
public:
	C_vampireGrab(int damage, float speed, double focusGain, std::string name, C_fighter* pMe, int lifeSteal);

	eResult use(C_fighter* vs);

protected:
	void	win(C_fighter* vs);
	void	lose(C_fighter* vs);

	int m_lifeSteal;
};

