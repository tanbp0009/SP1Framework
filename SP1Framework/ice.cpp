#include "ice.h"
#include "InteractiveObjects.h"

double g_dCharBounceTime;
extern char mapCurrent[25][80];
extern double g_dElapsedTime;
extern SGameChar g_sChar;
extern double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

int a;
int b;
bool move;
bool ice_check()
{
	a = 0;
	b = 0;
	ice_movement();
	if ((mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '°' || mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '#') && (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] != ' '))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void ice_movement()
{
	if (g_sChar.playerdir == '^')
	{
		a = -1;
	}
	if (g_sChar.playerdir == 'v')
	{
		a = 1;
	}
	if (g_sChar.playerdir == '<')
	{
		b = -1;
	}
	if (g_sChar.playerdir == '>')
	{
		b = 1;
	}
}
void ice_movement_loop()
{
		a = 0;
		b = 0;
		ice_movement();
				if (mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '°' || mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '#' || (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '°' && mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '#') || (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '#' && mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '°'))
				{
					move = true;
				}
				if (mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == ' ' && mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '°')
				{
					move = true;
				}
				if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '#' && mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == ' ')
				{
					move = false;
				}
				if (move == true)
				{
					movement_interaction();
				}
}
