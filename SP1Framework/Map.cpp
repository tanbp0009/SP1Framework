#include "Map.h"


// defined in game.cpp
extern Console g_Console;
extern EGAMESTATES g_eGameState;
extern bool mapSaved[5];
extern int level;
char savemap[5][25][80];
char maparray[25][80];

void GetMap(std::string Inlevel)
{
	char ch;
	int row = 0;
	int col = 0;

	std::fstream fin(Inlevel, std::fstream::in);
	while (fin >> std::noskipws >> ch)
	{
		maparray[row][col] = ch;
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
			g_Console.writeToBuffer(setmapcoord, maparray[setmapcoord.Y][setmapcoord.X], 0x0A);
		}
	}
}

void loadLevel()
{
	if (mapSaved[level] == false)
	{
		if (level == 2)
		{
			GetMap("config/Level2.txt");
			mapSaved[level] = true;
		}
		if (level == 1)
		{
			GetMap("config/level1.txt");
			mapSaved[level] = true;
		}
	}

	else
	{
		if (level == 2)
		{
			GetSavedMap(level);
		}
		if (level == 1)
		{
			GetSavedMap(level);
		}	
	}
	g_eGameState = S_GAME;
}

void savelevel(int Inlevel)
{
	COORD setmapcoord;
	for (setmapcoord.Y = 0; setmapcoord.Y < 25; setmapcoord.Y++)
	{
		for (setmapcoord.X = 0; setmapcoord.X < 80; setmapcoord.X++)
		{
			savemap[Inlevel][setmapcoord.Y][setmapcoord.X] = maparray[setmapcoord.Y][setmapcoord.X];	
		}
	}
	mapSaved[Inlevel] = true;
}

void GetSavedMap(int Inlevel)
{
	COORD setmapcoord;
	for (setmapcoord.Y = 0; setmapcoord.Y < 25; setmapcoord.Y++)
	{
		for (setmapcoord.X = 0; setmapcoord.X < 80; setmapcoord.X++)
		{
			maparray[setmapcoord.Y][setmapcoord.X] = savemap[Inlevel][setmapcoord.Y][setmapcoord.X];
		}
	}
}