#include "walkover.h"

extern char mapCurrent[25][80];
extern SGameChar g_sChar;
extern int level;
extern EGAMESTATES g_eGameState;

void trap()
{
	if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '#')
	{
		g_sChar.lives--;
	}
	if (g_sChar.lives == 0)
	{
		level = 19;
		g_eGameState = S_LOADLEVEL;
	}
}

void fallingfloor()
{
	if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '/')
	{
		mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'Û';
	}
}
void portal()
{
	if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '0')
	{
		mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] += 0;
	}
}