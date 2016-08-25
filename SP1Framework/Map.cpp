#include "Map.h"

// defined in game.cpp
extern Console g_Console;
extern EGAMESTATES g_eGameState;
extern SGameChar g_sChar;
extern int level;
extern int gmmc;
char fogmap[20][25][80];
char mapCurrent[25][80];
char fogwrap[20][25][25];


void GetNewMap(std::string filelocation)
{
	std::string fileaffix = "config/";
	fileaffix += filelocation;
	std::ifstream infile(fileaffix);
	fileaffix = "save/";
	fileaffix += filelocation;
	std::ofstream outfile(fileaffix);
	std::string content = "";
	int i;

	for (i = 0; infile.eof() != true; i++) // get content of infile
		content += infile.get();

	i--;
	content.erase(content.end() - 1);     // erase last character

	infile.close();

	outfile << content;                 // output
	outfile.close();
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
			case '�':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				break;
			case '�':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0E);
				break;
			case '�':
				if (level == 0)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x08);
				break;
			case '�':case '�':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				break;
			case '�':
				if (level == 16)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x03);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				break;
			case',':case'.':case'-':case'"':case'_':case'\\':case'=':case'|':case'/':case'l':case'\'':case'O':
				if (level == 19)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
			case '(': case '%': case '*': case '^':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				break;
			case ')':
				if (level == 1 || level == 19)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
			case 'o':
				if (level == 19 || level == 1)
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
	std::string filelocation;

	switch (Inlevel)
	{
	case 0:
		filelocation = "save/Title_Game.txt";
		break;
	case 1:
		filelocation = "save/Main_Menu.txt";
		break;
	case 2:
		filelocation = "save/Inventory.txt";
		break;
	case 14:
		filelocation = "save/Vault_Key_1.txt";
		break;
	case 15:
		filelocation = "save/Vault_Connect.txt";
		break;
	case 16:
		filelocation = "save/Vault_Key_2.txt";
		break;
	case 17:
		filelocation = "save/Vault_Key_3.txt";
		break;
	case 18:
		filelocation = "save/Vault_Room.txt";
		break;
	case 19:
		filelocation = "save/Game_Over.txt";
		break;
	}

	std::ofstream myfile(filelocation);
	if (myfile.is_open())
	{
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				myfile << mapCurrent[i][j];
			}
			myfile << "\n";
		}
		myfile.close();
	}
}

void loadLevel()
{
	if (/*level == 14 || level == 15 || */level == 16 || level == 17 || level == 18)
	{
		GetSavedMap(level);
		g_eGameState = S_GAME;
	}
	if (level == 14 || level == 15)
	{
		GetSavedMap(level);
		getfog(level);
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
//-------------------------------------------------------------
/*void getfog(int Inlevel)
{
	COORD setmapcoord;
	COORD playerpos = g_sChar.m_cLocation;
	memset(fogwrap, ' ', sizeof(fogwrap[0][0][0]) * (25 * 80));
	for (int y = playerpos.Y - 1; y < playerpos.Y + 1; y++)
		for (int x = playerpos.X - 1; x < playerpos.X + 1; x++)
		{
			fogwrap[Inlevel][y][x] = fogmap[Inlevel][y][x];
		}
	for (setmapcoord.Y = 0; setmapcoord.Y < 25; setmapcoord.Y++)
		for (setmapcoord.X = 0; setmapcoord.X < 25; setmapcoord.X++)
		{
			mapCurrent[setmapcoord.Y][setmapcoord.X] = fogwrap[Inlevel][setmapcoord.Y][setmapcoord.X];
		}
}*/
//-------------------------------------------------------------
void GetSavedMap(int Inlevel)	
{
	std::string filelocation;
	switch (Inlevel)
	{
	case 0:
		filelocation = "config/Title_Game.txt";
		break;
	case 1:
		filelocation = "config/Main_Menu.txt";
		break;
	case 2:
		filelocation = "config/Inventory.txt";
		break;
	case 14:
		filelocation = "save/Vault_Key_1.txt";
		break;
	case 15:
		filelocation = "save/Vault_Connect.txt";
		break;
	case 16:
		filelocation = "save/Vault_Key_2.txt";
		break;
	case 17:
		filelocation = "save/Vault_Key_3.txt";
		break;
	case 18:
		filelocation = "save/Vault_Room.txt";
		break;
	case 19:
		filelocation = "config/Game_Over.txt";
		break;
	}
	char ch;
	int row = 0;
	int col = 0;

	std::fstream fin(filelocation, std::fstream::in);
	while (fin >> std::noskipws >> ch)
	{
		fogmap[Inlevel][row][col] = ch;
		mapCurrent[row][col] = ch;
		col++;
		if (col == 81)
		{
			col = 0;
			row++;
		}
	}
}

void NewLevel()
{
	GetNewMap("Title_Game.txt");
	GetNewMap("Main_Menu.txt");
	GetNewMap("Inventory.txt");
	GetNewMap("Vault_Key_1.txt");
	GetNewMap("Vault_Connect.txt");
	GetNewMap("Vault_Key_2.txt");
	GetNewMap("Vault_Key_3.txt");
	GetNewMap("Vault_Room.txt");
	GetNewMap("Game_Over.txt");

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