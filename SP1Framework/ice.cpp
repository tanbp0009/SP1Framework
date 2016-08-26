#include "ice.h"
#include "InteractiveObjects.h"

extern char mapCurrent[25][80];
extern SGameChar g_sChar;
int a;
int b;
bool ice_check()
{
	a = 0;
	b = 0;
	ice_movement();
	if (mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '°' || mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '#')
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
	while (ice_check() == true)
	{
			ice_movement();
			movement_interaction();
			if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '#' && mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == ' ')
			{
				break;
			}
			if (mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '°' || mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '#' || (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '°' && mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '#') || (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '#' && mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '°'))
			{
				movement_interaction();
				ice_check();
			}
			if (mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == ' ' && mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '°')
			{
				movement_interaction();
				break;
			}
	};
}
