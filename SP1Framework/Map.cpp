#include "Map.h"


// defined in game.cpp
extern Console g_Console;
int maparray[25][80];
int row = 0;
int col = 0;
void GetMap(std::string Inlevel)
{
	char ch;
	row = 0;
	col = 0;

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