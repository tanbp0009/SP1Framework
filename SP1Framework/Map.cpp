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
	//std::string line;
	//std::ifstream myfile("config/example.txt");
	//COORD v;
	//v.Y = -1;
	//if (myfile.is_open())
	//{
	//	while (getline(myfile, line))
	//	{
	//		v.X = 0;
	//		v.Y += 1;
	//		g_Console.writeToBuffer(v, line, 0x0A);
	//	}

	//	myfile.close();
	////	maprendered = true;
	//}

	
	//std::fstream fin("config/example.txt", std::fstream::in);
	//while (fin >> std::noskipws >> ch) 
	//{

	//	g_Console.writeToBuffer(v, ch, 0x0A);
	//	v.X++;
	//	if (v.X == 80)
	//	{
	//		v.X = -1;
	//		v.Y++;
	//	}
	//}

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