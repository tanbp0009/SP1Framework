#include "Map.h"


// defined in game.cpp
extern Console g_Console;
extern EGAMESTATES g_eGameState;
extern int level;
char savemap[20][25][80];
char mapCurrent[25][80];

void GetMap(std::string filelocation, int Inlevel)
{
	char ch;
	int row = 0;
	int col = 0;

	std::fstream fin(filelocation, std::fstream::in);
	while (fin >> std::noskipws >> ch)
	{
		savemap[Inlevel][row][col] = ch;
		//	g_Console.writeToBuffer(v, ch, 0x0A);
		col++;
		if (col == 81)
		{
			col = 0;
			row++;
		}
	}
}

void SetMap()
{
	COORD setmapcoord;

	for (setmapcoord.Y = 0; setmapcoord.Y < 25; setmapcoord.Y++)
	{
		for (setmapcoord.X = 0; setmapcoord.X < 80; setmapcoord.X++)
		{
			switch (mapCurrent[setmapcoord.Y][setmapcoord.X])
			{
			case '#':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				break;
			case 'ê':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				break;
			case 'Ÿ':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0E);
				break;
			case 'Û':
				if (level == 8)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x08);
				break;
			case '±':case '²':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				break;
			case '°':
				if (level == 3)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x03);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				break;
			case',':case'.':case'-':case'"':case'_':case'\\':case'=':case'|':case'/':case'l':case'\'':case'O':
				if (level == 9)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
			case '(': case '%': case '*': case '^':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				break;
			case ')':
				if (level == 0 || level == 9)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
			case 'o':
				if (level == 9 || level == 0)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
			default:
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
			}
		}
	}
}

void savelevel(int Inlevel)
{
	COORD setmapcoord;
	for (setmapcoord.Y = 0; setmapcoord.Y < 25; setmapcoord.Y++)
	{
		for (setmapcoord.X = 0; setmapcoord.X < 80; setmapcoord.X++)
		{
			savemap[Inlevel][setmapcoord.Y][setmapcoord.X] = mapCurrent[setmapcoord.Y][setmapcoord.X];
		}
	}
}

void loadLevel()
{
	if (level == 14 || level == 15 || level == 16 || level == 17 || level == 18)
	{
		GetSavedMap(level);
		g_eGameState = S_GAME;
	}
	if (level == 19)
	{
		GetSavedMap(level);
		g_eGameState = S_GAMEOVER;
	}
	if (level == 1)
	{
		GetSavedMap(level);
		g_eGameState = S_MAINMENU;
	}
	if (level == 0)
	{
		GetSavedMap(level);
		g_eGameState = S_TITLE;
	}
	if (level == 2)
	{
		GetSavedMap(level);
		g_eGameState = S_INVENTORY;

	}
}

void GetSavedMap(int Inlevel)
{
	COORD setmapcoord;
	for (setmapcoord.Y = 0; setmapcoord.Y < 25; setmapcoord.Y++)
	{
		for (setmapcoord.X = 0; setmapcoord.X < 80; setmapcoord.X++)
		{
			mapCurrent[setmapcoord.Y][setmapcoord.X] = savemap[Inlevel][setmapcoord.Y][setmapcoord.X];
		}
	}
}

void preloadLevel()
{
	GetMap("config/Title_Game.txt", 0);
	GetMap("config/Main_Menu.txt", 1);
	GetMap("config/Inventory.txt", 2);
	GetMap("config/Vault_Key_1.txt", 14);
	GetMap("config/Vault_Connect.txt", 15);
	GetMap("config/Vault_Key_3.txt", 16);
	GetMap("config/Vault_Key_4.txt", 17);
	GetMap("config/Vault_Room.txt", 18);
	GetMap("config/Game_Over.txt", 19);
}

COORD GetCharCoord(char InChar)
{
	COORD getcoord;
	for (getcoord.Y = 0; getcoord.Y < 25; getcoord.Y++)
	{
		for (getcoord.X = 0; getcoord.X < 80; getcoord.X++)
		{
			if (mapCurrent[getcoord.Y][getcoord.X] == InChar)
			{
				return getcoord;
			}
		}
	}
	return getcoord;
}