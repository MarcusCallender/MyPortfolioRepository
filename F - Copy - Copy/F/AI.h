#pragma once

#include "Controler.h"

#include <list>

class C_AI: public C_controler
{
public:
	C_AI();
	~C_AI();

	void input(C_move ** moves);

	void result(eResult res, C_fighter* vs);

	void receveResult(eAI_Result res, eAI_Type type);

	int predictMoveConfidence();

	eAI_Type findLowest();
	eAI_Type findHighest();

	void useAttack(C_move** moves);
	void useBlock(C_move** moves);
	void useThrow(C_move** moves);

protected:
	std::list <eResult> m_eResults;
	std::list <C_move*> m_moves;

	eAI_Type m_previousType;
	eAI_Result m_previousResult;

	int m_defaultMove;

	int m_data[AI_TYPE_TOTAL][AI_RES_TOTAL][AI_TYPE_TOTAL];
};

