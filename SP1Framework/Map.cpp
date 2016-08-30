#include "Map.h"

// defined in game.cpp
extern int playernum;
extern Console g_Console;
extern EGAMESTATES g_eGameState;
extern SGameChar g_sChar;
extern SGameEnemy g_sEnemy;
extern int level;
extern int selection;
char mapCurrent[25][80];
COORD doorcoord;
COORD door2coord;


void GetNewMap(std::string filelocation, int InSaveFileNo)
{
	std::string fileaffix = "config/";
	fileaffix += filelocation;
	std::ifstream infile(fileaffix);
	fileaffix = "save/save";
	fileaffix += std::to_string(InSaveFileNo);
	fileaffix += "/";
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
				case 'D':
				if (level == 15)
				{
					if (setmapcoord.Y < 10)
					{
						if (g_sChar.keys == 3)
						{
							g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
						}
						else
						{
							g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0C);
						}
					}
					else
					{
						g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
					}
				}
				else
				{
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				}
				break;
			case '#':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				break;
			case 'ê':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				break;
			case 'Ÿ':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0E);
				break;
			case 'è':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
			case 'Ü':
				if (level == 4)
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0C);
				break;
			case 'Û':
				if (level == 0)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0C);
				else if (level == 4)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x08);
				break;
			case '±':case '²':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				break;
			case '°':
				if (level == 16)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x03);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				break;
			case',':case'.':case'"':case'_':case'\\':case'=':case'|':case'/':case'l':case'\'':case'O':
				if (level == 19)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				else if (level == 5)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06); 
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
			case '%': case '*': case '^':
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				break;
			case '(':
				if (level == 1)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else if (level == 4)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x05);
				else if (level == 5)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
				{
					door2coord = setmapcoord;
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				}
				break;
			case ')':
				if (level == 1 || level == 19)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else if (level == 4)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x05);
				else if (level == 5)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
				{
					doorcoord = setmapcoord;
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				}
				break;
			case 'o':
				if (level == 19 || level == 1)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				if (level == 3)
				{
					if (setmapcoord.Y < 16)
					{
						g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
					}
					else
					{
						g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
					}
				}
				break;
			//case '™':
			//	g_sEnemy.m_cLocation = setmapcoord;
			//	g_Console.writeToBuffer(setmapcoord, " ", 0x00);
			//	break;
			case 'ß':
				if (level == 0)
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0C);
				else if (level == 4)
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else if (level == 5)
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06); 
				else
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
				case '<': case '>':
				if (level == 4)
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0D);
				else if (level == 5)
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
				case '-':
				if (level == 19)
						g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x04);
				else if (level == 5)
						g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
				case '`': case '~': case ':':
				if (level == 5)
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x06);
				else
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
				break;
				case '§':
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0E);
					break;
				case '+':
					g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x00);
					break;
			default:
				g_Console.writeToBuffer(setmapcoord, mapCurrent[setmapcoord.Y][setmapcoord.X], 0x0A);
			}
		}
	}
}

void savelevel(int Inlevel, std::string filedir)
{
	std::string filelocation = "save/save";
	filelocation += filedir;
	switch (Inlevel)
	{
	case 0:
		filelocation += "/Title_Game.txt";
		break;
	case 1:
		filelocation += "/Main_Menu.txt";
		break;
	case 2:
		filelocation += "/Inventory.txt";
		break;
	case 3:
		filelocation += "/Instruction.txt";
		break;
	case 4:
		filelocation += "/Win.txt";
		break;
	case 5:
		filelocation += "/Name.txt";
		break;
	case 7:
		filelocation += "/Light_01.txt";
		break;
	case 8:
		filelocation += "/Light_02.txt";
		break;
	case 9:
		filelocation += "/Light_03.txt";
		break;
	case 10:
		filelocation += "/Light_04.txt";
		break;
	case 11:
		filelocation += "/Light_05.txt";
		break;
	case 14:
		filelocation += "/Vault_Key_1.txt";
		break;
	case 15:
		filelocation += "/Vault_Connect.txt";
		break;
	case 16:
		filelocation += "/Vault_Key_2.txt";
		break;
	case 17:
		filelocation += "/Vault_Key_3.txt";
		break;
	case 18:
		filelocation += "/Vault_Room.txt";
		break;
	case 19:
		filelocation += "/Game_Over.txt";
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
	selection = 0;
	if (level == 7 || level == 8 || level == 9 || level == 10 || level == 11 || level == 14 || level == 15 || level == 16 || level == 17 || level == 18)
	{
		GetSavedMap(level, std::to_string(playernum));
		g_eGameState = S_GAME;
	}
	if (level == 19)
	{
		GetSavedMap(level, std::to_string(playernum));
		g_eGameState = S_GAMEOVER;
	}
	if (level == 1)
	{
		GetSavedMap(level, std::to_string(playernum));
		g_eGameState = S_MAINMENU;
	}
	if (level == 0)
	{
		GetSavedMap(level, std::to_string(playernum));
		g_eGameState = S_TITLE;
	}
	if (level == 2)
	{
		GetSavedMap(level, std::to_string(playernum));
		g_eGameState = S_INVENTORY;

	}
	if (level == 3)
	{
		GetSavedMap(level, std::to_string(playernum));
		g_eGameState = S_INSTRUCTION;

	}
	if (level == 4)
	{
		GetSavedMap(level, std::to_string(playernum));
		g_eGameState = S_WIN;

	}
	if (level == 5)
	{
		GetSavedMap(level, std::to_string(playernum));
		g_eGameState = S_NAME;
	}
	if (level == 6)
	{
		GetSavedMap(level, std::to_string(playernum));
		g_eGameState = S_LOADSAVE;
	}
}

void GetSavedMap(int Inlevel, std::string filedir)	
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
	case 3:
		filelocation = "config/Instruction.txt";
		break;
	case 4:
		filelocation = "config/Win.txt";
		break;
	case 5:
		filelocation = "config/Name.txt";
		break;
	case 6:
		filelocation = "config/Load_Save_File.txt";
		break;
	case 7:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Light_01.txt";
		break;
	case 8:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Light_02.txt";
		break;
	case 9:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Light_03.txt";
		break;
	case 10:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Light_04.txt";
		break;
	case 11:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Light_05.txt";
		break;
	case 14:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Vault_Key_1.txt";
		break;
	case 15:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Vault_Connect.txt";
		break;
	case 16:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Vault_Key_2.txt";
		break;
	case 17:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Vault_Key_3.txt";
		break;
	case 18:
		filelocation = "save/save";
		filelocation += filedir;
		filelocation += "/Vault_Room.txt";
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
		mapCurrent[row][col] = ch;
		col++;
		if (col == 81)
		{
			col = 0;
			row++;
		}
	}
}

void NewLevel(int InSaveFileNo)
{
	GetNewMap("Save_Data.txt", InSaveFileNo);
	GetNewMap("Title_Game.txt", InSaveFileNo);
	GetNewMap("Main_Menu.txt", InSaveFileNo);
	GetNewMap("Inventory.txt", InSaveFileNo);
	GetNewMap("Instruction.txt", InSaveFileNo);
	GetNewMap("Light_01.txt", InSaveFileNo);
	GetNewMap("Light_02.txt", InSaveFileNo);
	GetNewMap("Light_03.txt", InSaveFileNo );
	GetNewMap("Light_04.txt", InSaveFileNo);
	GetNewMap("Light_05.txt", InSaveFileNo);
	GetNewMap("Vault_Key_1.txt", InSaveFileNo);
	GetNewMap("Vault_Connect.txt", InSaveFileNo);
	GetNewMap("Vault_Key_2.txt", InSaveFileNo);
	GetNewMap("Vault_Key_3.txt", InSaveFileNo);
	GetNewMap("Vault_Room.txt", InSaveFileNo);
	GetNewMap("Game_Over.txt", InSaveFileNo);
	GetNewMap("Win.txt", InSaveFileNo);
	GetNewMap("Name.txt", InSaveFileNo);
	GetNewMap("Load_Save_File.txt", InSaveFileNo);
}