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
		if (g_sChar.lives == 2)
		{
			PlaySound(TEXT("audio/life.wav"), NULL, SND_ASYNC);
		}
		if (g_sChar.lives == 1)
		{
			PlaySound(TEXT("audio/life2.wav"), NULL, SND_ASYNC);
		}
	}
	if (g_sChar.lives == 0)
	{
		PlaySound(TEXT("audio/life3.wav"), NULL, SND_ASYNC);
		level = 19;
		g_eGameState = S_LOADLEVEL;
	}
}

void fallingfloor()
{
	if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '/')
	{
		mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'X';
	}
}
void teleport()
{
	if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '0')
	{
		g_sChar.m_cLocation.Y -= 3;
	}
}