#include "Map.h"


// defined in game.cpp
extern Console g_Console;
extern EGAMESTATES g_eGameState;
extern int level;
char savemap[10][25][80];
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
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
			case '±':case '²':case '°':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				break;
			case',':case'.':case'-':case'"':case'_':case'\\':case'=':case'|':case'/':case'l':case'\'':case'O':
				if (level == 9)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
			case '(':case ')': case 'o': case '%': case '*': case '^':
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
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
	if (level == 1 || level == 2 || level == 3 || level == 4 || level == 5)
	{
		GetSavedMap(level);
		g_eGameState = S_GAME;
	}
	if (level == 9)
	{
		GetSavedMap(level);
		g_eGameState = S_GAMEOVER;
	}
	if (level == 0)
	{
		GetSavedMap(level);
		g_eGameState = S_MAINMENU;
	}
	if (level == 8)
	{
		GetSavedMap(level);
		g_eGameState = S_TITLE;
	}
	if (level == 7)
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
	GetMap("config/level1.txt", 1);
	GetMap("config/Level2.txt", 2);
	GetMap("config/Level3.txt", 3);
	GetMap("config/Level4.txt", 4);
	GetMap("config/Game_Over.txt", 9);
	GetMap("config/Main_Menu.txt", 0);
	GetMap("config/Title_Game.txt", 8);
	GetMap("config/Inventory.txt", 7);
}