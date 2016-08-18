#include "InteractiveObjects.h"

extern char mapCurrent[25][80];
extern SGameChar g_sChar;
extern int level;
extern bool mapSaved;
extern EGAMESTATES g_eGameState;

char objectinfront;
COORD ObjectPosition;

bool PlayerFacingObject()
{
	ObjectPosition.X = 0;
	ObjectPosition.Y = 0;
	objectinfront = ' ';
	if (g_sChar.playerdir == 'u' && mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X;
		ObjectPosition.Y = g_sChar.m_cLocation.Y-1;
		objectinfront = mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X];
		return true;
	}
	if (g_sChar.playerdir == 'd' && mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X;
		ObjectPosition.Y = g_sChar.m_cLocation.Y + 1;
		objectinfront = mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X];
		return true;
	}
	if (g_sChar.playerdir == 'l' && mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X-1;
		ObjectPosition.Y = g_sChar.m_cLocation.Y;
		objectinfront = mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1];
		return true;
	}
	if (g_sChar.playerdir == 'r' && mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X + 1;
		ObjectPosition.Y = g_sChar.m_cLocation.Y;
		objectinfront = mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1];
		return true;
	}
	else
	{
		return false;
	}
}

void interactobjectinfront()
{
	if (PlayerFacingObject() == true)
	{
		switch (objectinfront)
		{
		case 'o': door(); // game logic for the splash screen
			break;
		case '|': something(); // gameplay logic when we are in the game
			break;
		case 'D': nextlevel(); // gameplay logic when we are in the game
			break;
		}
	}
}

int a = 0;
int b = 0;
void door()
{
	{
		int y;
		int x;
		for (y = 0; y < 25; y++)
		{
			for (x = 0; x < 80; x++)
			{
				if (mapCurrent[y][x] == ')')
				{
					a = x;
					b = y;
					break;
				}
			}
		}
	}
	if (mapCurrent[b][a] == ')')
	{
		mapCurrent[b][a] = ' ';
	}
	else if (mapCurrent[b][a] == ' ')
	{
		mapCurrent[b][a] = ')';
	}
}

void something()
{
	mapCurrent[ObjectPosition.Y][ObjectPosition.X] = ' ';
}

void nextlevel()
{
	savelevel(level);
	if (ObjectPosition.X > 40)
	{
		g_sChar.m_cLocation.X = 1;
		level = 2;
		g_eGameState = S_LOADLEVEL;
	}
	if (ObjectPosition.X < 40)
	{
		g_sChar.m_cLocation.X = 78;
		level = 1;
		g_eGameState = S_LOADLEVEL;
	}
}
void trap()
{
	if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '#')
	{
		g_sChar.lives--;
	}
	if (g_sChar.lives == 0)
	{
		g_eGameState = S_LOSEGAME;
	}

}