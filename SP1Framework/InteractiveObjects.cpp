#include "InteractiveObjects.h"

extern Console g_Console;
extern char mapCurrent[25][80];
extern SGameChar g_sChar;
extern int level;
extern EGAMESTATES g_eGameState;

char objectinfront;
COORD ObjectPosition;

char GetObjectChar()
{
	ObjectPosition.X = 0;
	ObjectPosition.Y = 0;
	char ch;
	if (g_sChar.playerdir == 'u' && mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X;
		ObjectPosition.Y = g_sChar.m_cLocation.Y-1;
		return ch = mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X];
	}
	if (g_sChar.playerdir == 'd' && mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X;
		ObjectPosition.Y = g_sChar.m_cLocation.Y + 1;
		return ch = mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X];
	}
	if (g_sChar.playerdir == 'l' && mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X-1;
		ObjectPosition.Y = g_sChar.m_cLocation.Y;
		return ch = mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1];
	}
	if (g_sChar.playerdir == 'r' && mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X + 1;
		ObjectPosition.Y = g_sChar.m_cLocation.Y;
		return ch = mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1];
	}
}

void interactobjectinfront()
{

	switch (GetObjectChar())
	{
	case 'o': door(); // game logic for the splash screen
		break;
	case 'Û': something(); // gameplay logic when we are in the game
		break;
	case 'D': nextlevel(); // gameplay logic when we are in the game
		break;
	case 'ê': moveboulder(); // gameplay logic when we are in the game
		break;
	case 'Ÿ': keys(); // gameplay logic when we are in the game
		break;
	case 'è': teletospawn(); // gameplay logic when we are in the game
		break;
	}
}

COORD doorcoord;
void door()
{
	if (doorcoord.X == NULL)
		doorcoord = GetCharCoord(')');
	if (mapCurrent[doorcoord.Y][doorcoord.X] == ')')
	{
		mapCurrent[doorcoord.Y][doorcoord.X] = ' ';
	}
	else if (mapCurrent[doorcoord.Y][doorcoord.X] == ' ')
	{
		mapCurrent[doorcoord.Y][doorcoord.X] = ')';
	}
}
COORD door2coord;
void door2()
{
	door2coord = GetCharCoord('(');
	if (mapCurrent[door2coord.Y][door2coord.X] == '(')
	{
		mapCurrent[door2coord.Y][door2coord.X] = ' ';
	}
}
void something()
{
	mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
}

void nextlevel()
{
	savelevel(level);
	saveChar(g_sChar);
	switch (level)
	{
	case 14:
		if (ObjectPosition.X == 79)
		{
			g_sChar.m_cLocation.X = 1;
			level = 15;
			g_eGameState = S_LOADLEVEL;
		}
		break;
	case 15:
		if (ObjectPosition.X == 0)
		{
			g_sChar.m_cLocation.X = 78;
			level = 14;
			g_eGameState = S_LOADLEVEL;
		}
		if (ObjectPosition.X == 79)
		{
			g_sChar.m_cLocation.X = 1;
			level = 16;
			g_eGameState = S_LOADLEVEL;
		}
		if (ObjectPosition.Y == 24)
		{
			g_sChar.m_cLocation.Y = 1;
			level = 17;
			g_eGameState = S_LOADLEVEL;
		}
		if (ObjectPosition.Y == 0)
		{
			g_sChar.m_cLocation.Y = 23;
			level = 18;
			g_eGameState = S_LOADLEVEL;
		}
		break;
	case 16:
		if (ObjectPosition.X == 0)
		{
			g_sChar.m_cLocation.X = 78;
			level = 15;
			g_eGameState = S_LOADLEVEL;
		}
		break;
	case 17:
		if (ObjectPosition.Y == 0)
		{
			g_sChar.m_cLocation.Y = 23;
			level = 15;
			g_eGameState = S_LOADLEVEL;
		}
	case 18:
		if (ObjectPosition.Y == 24)
		{
			g_sChar.m_cLocation.Y = 1;
			level = 15;
			g_eGameState = S_LOADLEVEL;
		}
	}
}


void moveboulder()
{
	if (g_sChar.playerdir == 'u')
	{
		if (mapCurrent[ObjectPosition.Y - 1][ObjectPosition.X] == ' ' || mapCurrent[ObjectPosition.Y - 1][ObjectPosition.X] == 'P')
		{
			mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
			mapCurrent[ObjectPosition.Y - 1][ObjectPosition.X] = 'ê';
			
		}
	}
	if (g_sChar.playerdir == 'd')
	{
		if (mapCurrent[ObjectPosition.Y + 1][ObjectPosition.X] == ' '|| mapCurrent[ObjectPosition.Y + 1][ObjectPosition.X] == 'P')
		{
			mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
			mapCurrent[ObjectPosition.Y + 1][ObjectPosition.X] = 'ê';
		}
	}
	if (g_sChar.playerdir == 'l')
	{
		if (mapCurrent[ObjectPosition.Y][ObjectPosition.X - 1] == ' ' || mapCurrent[ObjectPosition.Y][ObjectPosition.X - 1] == 'P')
		{
			mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
			if (mapCurrent[ObjectPosition.Y][ObjectPosition.X - 1] == 'P')
			{
				door2();
			}
			mapCurrent[ObjectPosition.Y][ObjectPosition.X - 1] = 'ê';
		}
	}
	if (g_sChar.playerdir == 'r')
	{
		if (mapCurrent[ObjectPosition.Y][ObjectPosition.X + 1] == ' ' || mapCurrent[ObjectPosition.Y][ObjectPosition.X + 1] == 'P')
		{
			mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
			mapCurrent[ObjectPosition.Y][ObjectPosition.X + 1] = 'ê';
		}
	}
}

bool ice_check()
{
	if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '°' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '#' || mapCurrent[ObjectPosition.Y][ObjectPosition.X + 1] != ' ' || mapCurrent[ObjectPosition.Y][ObjectPosition.X - 1] != ' ' || mapCurrent[ObjectPosition.Y - 1][ObjectPosition.X] != ' ' || mapCurrent[ObjectPosition.Y + 1][ObjectPosition.X] != ' ')
	{
		return true;
	}
	else
		return false;
}
void keys()
{
	if (mapCurrent[ObjectPosition.Y][ObjectPosition.X] == 'Ÿ')
	{
		g_sChar.keys++;
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
	}
}

void teletospawn()
{
	g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
	g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;

	savelevel(level);
	saveChar(g_sChar);
	level = 15;
	g_eGameState = S_LOADLEVEL;
}