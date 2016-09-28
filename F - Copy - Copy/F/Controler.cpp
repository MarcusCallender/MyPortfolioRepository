#include "Controler.h"

#include "Fighter.h"

#include "Dash.h"
#include "DSPD_017.h"
#include "Fenrir.h"
#include "Lance.h"
#include "Robo.h"
#include "Rush.h"
#include "Tarja.h"
#include "Wave.h"

C_controler::C_controler()
{
}

void C_controler::result(eResult res, C_fighter* vs)
{
}

void C_controler::setFighter(C_fighter* player)
{
	m_pPlayer = player;
}

void C_controler::receveResult(eAI_Result res, eAI_Type type)
{
}

