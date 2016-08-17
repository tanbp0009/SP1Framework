#include "InteractiveObjects.h"

extern char maparray[25][80];
extern SGameChar g_sChar;
extern int level;
extern bool mapSaved[5];
extern EGAMESTATES g_eGameState;

char objectinfront;
COORD ObjectPosition;

bool PlayerFacingObject()
{
	ObjectPosition.X = 0;
	ObjectPosition.Y = 0;
	objectinfront = ' ';
	if (g_sChar.playerdir == 'u' && maparray[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X;
		ObjectPosition.Y = g_sChar.m_cLocation.Y-1;
		objectinfront = maparray[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X];
		return true;
	}
	if (g_sChar.playerdir == 'd' && maparray[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X;
		ObjectPosition.Y = g_sChar.m_cLocation.Y + 1;
		objectinfront = maparray[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X];
		return true;
	}
	if (g_sChar.playerdir == 'l' && maparray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X-1;
		ObjectPosition.Y = g_sChar.m_cLocation.Y;
		objectinfront = maparray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1];
		return true;
	}
	if (g_sChar.playerdir == 'r' && maparray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != ' ')
	{
		ObjectPosition.X = g_sChar.m_cLocation.X + 1;
		ObjectPosition.Y = g_sChar.m_cLocation.Y;
		objectinfront = maparray[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1];
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
				if (maparray[y][x] == ')')
				{
					a = x;
					b = y;
					break;
				}
			}
		}
	}
	if (maparray[b][a] == ')')
	{
		maparray[b][a] = ' ';
	}
	else if (maparray[b][a] == ' ')
	{
		maparray[b][a] = ')';
	}
}

void something()
{
	maparray[ObjectPosition.Y][ObjectPosition.X] = ' ';
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