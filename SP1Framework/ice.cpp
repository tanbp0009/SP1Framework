#include "ice.h"
#include "InteractiveObjects.h"

extern char mapCurrent[25][80];
extern SGameChar g_sChar;
void ice_up()
{
	while (ice_check() == true)
	{
		g_sChar.m_cLocation.Y--;
		trap();
		fallingfloor();
		ice_check();
		if (mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == '#')
		{
			g_sChar.m_cLocation.Y--;
			trap();
			fallingfloor();
		}
		if (mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '°')
		{
			break;
		}
	};
}
void ice_down()
{
	while (ice_check() == true)
	{
		g_sChar.m_cLocation.Y++;
		trap();
		fallingfloor();
		ice_check();
		if (mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '#')
		{
			g_sChar.m_cLocation.Y++;
			trap();
			fallingfloor();
		}
		if (mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '°')
		{
			break;
		}
	}
}
void ice_left()
{
	while (ice_check() == true)
	{
		g_sChar.m_cLocation.X--;
		trap();
		fallingfloor();
		ice_check();
		if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '#')
		{
			g_sChar.m_cLocation.X--;
			trap();
			fallingfloor();
		}
		if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '°')
		{
			break;
		}
	}
}
void ice_right()
{
	while (ice_check() == true)
	{
		g_sChar.m_cLocation.X++;
		trap();
		fallingfloor();
		ice_check();
		if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '#')
		{
			g_sChar.m_cLocation.X++;
			trap();
			fallingfloor();
		}
		if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '°')
		{
			break;
		}
	}
}
void ice()
{
	if (ice_check() == true)
	{
		if (g_sChar.playerdir == 'u')
		{
			ice_up();
		}
		if (g_sChar.playerdir == 'd')
		{
			ice_down();
		}
		if (g_sChar.playerdir == 'l')
		{
			ice_left();
		}
		if (g_sChar.playerdir == 'r')
		{
			ice_right();
		}
	}
}
