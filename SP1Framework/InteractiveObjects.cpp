#include "InteractiveObjects.h"

extern Console g_Console;
extern char mapCurrent[25][80];
extern SGameChar g_sChar;
extern int level;
extern EGAMESTATES g_eGameState;
extern COORD doorcoord;
extern COORD door2coord;
extern int playernum;

char objectinfront;
COORD ObjectPosition;


char GetObjectChar()
{
	ObjectPosition.X = 0;
	ObjectPosition.Y = 0;
	char ch;
	if (g_sChar.playerdir == '^' && mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X;
		ObjectPosition.Y = g_sChar.m_cLocation.Y-1;
		return ch = mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X];
	}
	if (g_sChar.playerdir == 'v' && mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X;
		ObjectPosition.Y = g_sChar.m_cLocation.Y + 1;
		return ch = mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X];
	}
	if (g_sChar.playerdir == '<' && mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X-1;
		ObjectPosition.Y = g_sChar.m_cLocation.Y;
		return ch = mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1];
	}
	if (g_sChar.playerdir == '>' && mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != ' ')
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
	case '�': something(); // gameplay logic when we are in the game
		break;
	case 'D': nextlevel(); // gameplay logic when we are in the game
		break;
	case '�': moveboulder(); // gameplay logic when we are in the game
		break;
	case '�': keys(); // gameplay logic when we are in the game
		break;
	case '�': relic();
		break;
	case '�': relic();
		break;
	case '�': relic();
		break;
	case '�': relic();
		break;
	case '�': relic();
		break;
	case '�': relic();
		break;
	case '�': teletospawn(); // gameplay logic when we are in the game
		break;
	case '�': healthpack(); // gameplay logic when we are in the game
		break;
	case '-': VaultRoomPuzzleDoor();
		break;
	case '�': crown();
		break;
	case '�': lightswitch();
		break;
	}
}

void door()
{
	if (mapCurrent[doorcoord.Y][doorcoord.X] == ')')
	{
		mapCurrent[doorcoord.Y][doorcoord.X] = ' ';
	}
	else if (mapCurrent[doorcoord.Y][doorcoord.X] == ' ')
	{
		mapCurrent[doorcoord.Y][doorcoord.X] = ')';
	}
}

void door2()
{
	mapCurrent[door2coord.Y][door2coord.X] = ' ';
}
void something()
{
	mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
}

void nextlevel()
{
	savelevel(level, std::to_string(playernum));
	saveChar(g_sChar, std::to_string(playernum));
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
		if (g_sChar.keys == 3)
		{
			if (ObjectPosition.Y == 0)
			{
				g_sChar.m_cLocation.Y = 23;
				level = 18;
				g_eGameState = S_LOADLEVEL;
			}
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
	if (g_sChar.playerdir == '^')
	{
		if (mapCurrent[ObjectPosition.Y - 1][ObjectPosition.X] == ' ' || mapCurrent[ObjectPosition.Y - 1][ObjectPosition.X] == 'P')
		{
			mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
			mapCurrent[ObjectPosition.Y - 1][ObjectPosition.X] = '�';
			
		}
	}
	if (g_sChar.playerdir == 'v')
	{
		if (mapCurrent[ObjectPosition.Y + 1][ObjectPosition.X] == ' '|| mapCurrent[ObjectPosition.Y + 1][ObjectPosition.X] == 'P')
		{
			mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
			mapCurrent[ObjectPosition.Y + 1][ObjectPosition.X] = '�';
		}
	}
	if (g_sChar.playerdir == '<')
	{
		if (mapCurrent[ObjectPosition.Y][ObjectPosition.X - 1] == ' ' || mapCurrent[ObjectPosition.Y][ObjectPosition.X - 1] == 'P')
		{
			mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
			if (mapCurrent[ObjectPosition.Y][ObjectPosition.X - 1] == 'P')
			{
				door2();
			}
			mapCurrent[ObjectPosition.Y][ObjectPosition.X - 1] = '�';
		}
	}
	if (g_sChar.playerdir == '>')
	{
		if (mapCurrent[ObjectPosition.Y][ObjectPosition.X + 1] == ' ' || mapCurrent[ObjectPosition.Y][ObjectPosition.X + 1] == 'P')
		{
			mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
			mapCurrent[ObjectPosition.Y][ObjectPosition.X + 1] = '�';
		}
	}
}

void keys()
{
	if (mapCurrent[ObjectPosition.Y][ObjectPosition.X] == '�')
	{
		g_sChar.keys++;
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
	}
}

void relic()
{
	switch (mapCurrent[ObjectPosition.Y][ObjectPosition.X])
	{
	case '�':
		g_sChar.relic_scepter++;
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
		break;
	case '�':
		g_sChar.relic_amulet++;
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
		break;
	case '�':
		g_sChar.relic_tablet++;
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
		break;
	case '�':
		g_sChar.relic_ankh++;
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
		break;
	case '�':
		g_sChar.relic_goblet++;
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
		break;
	case '�':
		g_sChar.relic_scarab++;
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
		break;
	}
}

void teletospawn()
{
	g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
	g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;

	savelevel(level, std::to_string(playernum));
	saveChar(g_sChar, std::to_string(playernum));
	level = 15;
	g_eGameState = S_LOADLEVEL;
}
void healthpack()
{
	if (mapCurrent[ObjectPosition.Y][ObjectPosition.X] == '�')
	{
		if (g_sChar.lives != 3)
		{
			mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
			g_sChar.lives++;
		}
	}
}
void movement_interaction()
{
	if (g_sChar.playerdir == '^')
	{
		g_sChar.m_cLocation.Y--;
		trap();
		fallingfloor();
		teleport();
	}
	if (g_sChar.playerdir == 'v')
	{
		g_sChar.m_cLocation.Y++;
		trap();
		fallingfloor();
		teleport();
	}
	if (g_sChar.playerdir == '<')
	{
		g_sChar.m_cLocation.X--;
		trap();
		fallingfloor();
		teleport();
	}
	if (g_sChar.playerdir == '>')
	{
		g_sChar.m_cLocation.X++;
		trap();
		fallingfloor();
		teleport();
	}
}

void lightswitch()
{
	if (mapCurrent[ObjectPosition.Y][ObjectPosition.X] == '�')
	{
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
		level += 1;
		g_eGameState = S_LOADLEVEL;
	}
}

void VaultRoomPuzzleDoor()
{
	int floortrue = 0;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (mapCurrent[i][j] == '/')
			{
				floortrue++;
			}
		}
	}
	if (floortrue == 40 || floortrue == 0)
	{
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
	}
}
void crown()
{
	if (mapCurrent[ObjectPosition.Y][ObjectPosition.X] = '�')
	{
		mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
		level = 4;
		g_eGameState = S_LOADLEVEL;
	}
}