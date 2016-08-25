#include "ice.h"
#include "InteractiveObjects.h"

extern char mapCurrent[25][80];
extern SGameChar g_sChar;
int a;
int b;
void ice_movement()
{
	if (g_sChar.playerdir == 'u')
	{
		a = -1;
		g_sChar.m_cLocation.Y--;
		trap();
		fallingfloor();
	}
	if (g_sChar.playerdir == 'd')
	{
		a = 1;
		g_sChar.m_cLocation.Y++;
		trap();
		fallingfloor();
	}
	if (g_sChar.playerdir == 'l')
	{
		b = -1;
		g_sChar.m_cLocation.X--;
		trap();
		fallingfloor();
	}
	if (g_sChar.playerdir == 'r')
	{
		b = 1;
		g_sChar.m_cLocation.X++;
		trap();
		fallingfloor();
	}
}
void ice_movement_loop()
{
	a = 0;
	b = 0;
	while (ice_check() == true)
	{
		ice_movement();
		if (mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] == '#')
		{
			ice_movement();
		}
		if (mapCurrent[g_sChar.m_cLocation.Y + a][g_sChar.m_cLocation.X + b] != '°')
		{
			break;
		}
	};
}
void ice()
{
	ice_movement_loop();
}
