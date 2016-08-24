#include "map.h"

extern Console g_Console;
extern EGAMESTATES g_eGameState;
extern SGameChar g_sChar;
extern int level;

extern char savemap[20][25][80];
extern char mapCurrent[25][80];

char fogmap[20][25][80];
char fogmap2[20][25][80];


void GetFogMap(int Inlevel)
{
	COORD setmapcoord;
	memset(fogmap, ' ', sizeof(fogmap[0][0][0]) * (25 * 80)); // set blank array
	for (int VarY = g_sChar.m_cLocation.Y - 1; VarY <= g_sChar.m_cLocation.Y + 1; VarY++) // player Y range
	{
		for (int VarX = g_sChar.m_cLocation.X - 1; VarX <= g_sChar.m_cLocation.X + 1; VarX++) // player x range
		{
			fogmap[Inlevel][VarY][VarX] = savemap[Inlevel][VarY][VarX]; // set fog map's Player Y and X range to be map's Player's 
		}
	}
	for (setmapcoord.Y = 0; setmapcoord.Y < 25; setmapcoord.Y++)
	{
		for (setmapcoord.X = 0; setmapcoord.X < 80; setmapcoord.X++)
		{
			mapCurrent[setmapcoord.Y][setmapcoord.X] = fogmap[Inlevel][setmapcoord.Y][setmapcoord.X];
		}
	}
}