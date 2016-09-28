#ifndef __BASE_CONTAINER__
#define __BASE_CONTAINER__

#include "BaseFighter.h"
#include "BaseControler.h"
#include "Move.h"
#include "Status.h"

class C_BaseContainer
{
public:

	C_BaseContainer();
	~C_BaseContainer();

	C_move* getCurrentMove();
	static const int getNoOfMoves();
	void giveStatus(C_Status* pStatus);
	void removeStatus(C_Status* pStatus);
	virtual void showOptions();
	void showInput();
	virtual void input();
	//virtual eResult use();
	virtual void win();
	virtual void lose();

	void rest();

protected:

	C_BaseFighter* m_pFighter;
	C_BaseControler* m_pControler;

	const static int m_cs_noOfMoves = 6;
	C_move* m_pMoves[m_cs_noOfMoves];
	C_move* m_pCurrentMove;
	const static int m_cs_maxStatuses = 5;
	C_Status* m_pStatuses[5];
	
};

#endif // !__BASE_CONTAINER__

