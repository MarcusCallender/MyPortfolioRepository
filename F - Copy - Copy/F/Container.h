#pragma once

#include "Fighter.h"
#include "Controler.h"

class Container {
public:
	void charicterSelect();
	void controlerSelect();
	void init();

private:
	C_controler* m_pContrler;
	C_fighter* m_pFighter;
};

