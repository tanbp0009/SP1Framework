#include "InteractiveObjects.h"

extern int maparray[25][80];
extern SGameChar g_sChar;
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
		case ')': door(); // game logic for the splash screen
			break;
		case '|': something(); // gameplay logic when we are in the game
			break;
		}
	}
}

void door()
{

}

void something()
{
	maparray[ObjectPosition.Y][ObjectPosition.X] = ' ';
}
