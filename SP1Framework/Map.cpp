#include "Map.h"


// defined in game.cpp
extern Console g_Console;
extern EGAMESTATES g_eGameState;
extern bool mapSaved;
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
			if (mapCurrent[setmapcoord.Y][setmapcoord.X] == '�')
			{
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
			}
			if (mapCurrent[setmapcoord.Y][setmapcoord.X] == '�')
			{
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0F);
			}
			else
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
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
	mapSaved = true;
}

void loadLevel()
{
	if (mapSaved == false)
	{
		GetMap("config/level1.txt", 1);
		GetMap("config/Level2.txt", 2);
		GetMap("config/Level3.txt", 3);
		GetMap("config/Level4.txt", 4);
		GetMap("config/Lose page.txt",9);
		GetMap("config/Main_Menu.txt", 0);
		GetMap("config/Title_Game.txt", 8);
		mapSaved = true;
	}

	//else
	{
		if (level == 1 || level == 2 || level == 3 || level == 4 || level == 5)
		{
			GetSavedMap(level);
			g_eGameState = S_GAME;
		}
		if (level == 9)
		{
			GetSavedMap(level);
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
void losepage()
{
	level = 9;
	loadLevel();
	SetMap();
}