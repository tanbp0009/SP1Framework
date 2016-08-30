#include "charData.h"
extern int level;
extern EGAMESTATES g_eGameState;
extern Console g_Console;
extern int selection;
extern double g_dBounceTime;
extern double g_dElapsedTime;
extern bool g_abKeyPressed[K_COUNT];
extern int playernum;
extern SGameChar g_sChar;

void saveChar(struct SGameChar Ing_sChar, std::string filedir)
{
	std::string filelocation = "save/save";
	filelocation += filedir;
	filelocation += "/Save_Data.txt";
	std::ofstream myfile(filelocation);
	if (myfile.is_open())
	{
		myfile << Ing_sChar.name << "\n";
		myfile << Ing_sChar.playerdir << "\n";
		myfile << Ing_sChar.m_cLocation.Y << "\n";
		myfile << Ing_sChar.m_cLocation.X << "\n";
		myfile << Ing_sChar.lives << "\n";
		myfile << Ing_sChar.keys << "\n";
		myfile << level << "\n";
		myfile.close();
	}
}

struct SGameChar loadChar(struct SGameChar Ing_sChar, std::string filedir)
{
	std::string line;
	std::string filelocation = "save/save";
	filelocation += filedir;
	filelocation += "/Save_Data.txt";
	std::ifstream myfile(filelocation);
	if (myfile.is_open())
	{
		getline(myfile, line);
		Ing_sChar.name = line;
		getline(myfile, line);
		Ing_sChar.playerdir = line[0];
		getline(myfile, line);
		Ing_sChar.m_cLocation.Y = std::stoi(line);
		getline(myfile, line);
		Ing_sChar.m_cLocation.X = std::stoi(line);
		getline(myfile, line);
		Ing_sChar.lives = std::stoi(line);
		getline(myfile, line);
		Ing_sChar.keys = std::stoi(line);
		getline(myfile, line);
		Ing_sChar.currentlevel = std::stoi(line);
		myfile.close();
	}
	return Ing_sChar;
}

void renderSaveFile(struct SGameChar Ing_sChar)
{
	mainMenuButton();
	bool bSomethingHappened = false;
	SetMap();
	WORD color1, color2, color3, color4;
	COORD c;

	switch (selection)
	{
	case 0:
		color1 = 0x06;
		color2 = 0x07;
		color3 = 0x07;
		color4 = 0x07;
		break;
	case 1:
		color1 = 0x07;
		color2 = 0x06;
		color3 = 0x07;
		color4 = 0x07;
		break;
	case 2:
		color1 = 0x07;
		color2 = 0x07;
		color3 = 0x06;
		color4 = 0x07;
		break;
	case 3:
		color1 = 0x07;
		color2 = 0x07;
		color3 = 0x07;
		color4 = 0x06;
		break;
	}

	c.X = 15;
	c.Y = 12;

	std::ifstream myfile1("save/save1/Save_Data.txt");
	if (myfile1.is_open())
	{
		std::string line;
		getline(myfile1, line);

		g_Console.writeToBuffer(c, line, color1);
	}
	else
	{
		g_Console.writeToBuffer(c, "Empty File", color1);
	}

	c.X = 55;
	std::ifstream myfile2("save/save2/Save_Data.txt");
	if (myfile2.is_open())
	{
		std::string line;
		getline(myfile2, line);

		g_Console.writeToBuffer(c, line, color2);
	}
	else
	{
		g_Console.writeToBuffer(c, "Empty File", color2);
	}

	c.X = 15;
	c.Y = 18;
	std::ifstream myfile3("save/save3/Save_Data.txt");
	if (myfile3.is_open())
	{
		std::string line;
		getline(myfile3, line);

		g_Console.writeToBuffer(c, line, color3);
	}
	else
	{
		g_Console.writeToBuffer(c, "Empty File", color3);
	}

	c.X = 55;
	std::ifstream myfile4("save/save4/Save_Data.txt");
	if (myfile4.is_open())
	{
		std::string line;
		getline(myfile4, line);

		g_Console.writeToBuffer(c, line, color4);
	}
	else
	{
		g_Console.writeToBuffer(c, "Empty File", color4);
	}

	if (g_dBounceTime > g_dElapsedTime)
	{
		return;
	}
	else
	{
		if (g_abKeyPressed[K_UP])
		{
			if (selection == 2)
			{
				selection = 0;
			}
			if (selection == 3)
			{
				selection = 1;
			}
		}
		if (g_abKeyPressed[K_DOWN])
		{
			if (selection == 0)
			{
				selection = 2;
			}
			if (selection == 1)
			{
				selection = 3;
			}
		}
		if (g_abKeyPressed[K_LEFT])
		{
			if (selection == 1)
			{
				selection = 0;
			}
			if (selection == 3)
			{
				selection = 2;
			}
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			if (selection == 0)
			{
				selection = 1;
			}
			if (selection == 2)
			{
				selection = 3;
			}
		}
		if (g_abKeyPressed[K_SPACE])
		{
			switch (selection)
			{
			case 0:
				if (!checkFile("save/save1/Save_Data.txt"))
				{
					break;
				}
				playernum = 1;
				g_sChar = loadChar(Ing_sChar, std::to_string(playernum));
				level = g_sChar.currentlevel;
				g_eGameState = S_LOADLEVEL;
				break;
			case 1:
				if (!checkFile("save/save2/Save_Data.txt"))
				{
					break;
				}
				playernum = 2;
				g_sChar = loadChar(Ing_sChar, std::to_string(playernum));
				level = g_sChar.currentlevel;
				g_eGameState = S_LOADLEVEL;
				break;
			case 2:
				if (!checkFile("save/save3/Save_Data.txt"))
				{
					break;
				}
				playernum = 3;
				g_sChar = loadChar(Ing_sChar, std::to_string(playernum));
				level = g_sChar.currentlevel;
				g_eGameState = S_LOADLEVEL;
				break;
			case 3:
				if (!checkFile("save/save4/Save_Data.txt"))
				{
					break;
				}
				playernum = 4;
				g_sChar = loadChar(Ing_sChar, std::to_string(playernum));
				level = g_sChar.currentlevel;
				g_eGameState = S_LOADLEVEL;
				break;
			}
		}
		if (isKeyPressed(VK_DELETE))
		{
			if (selection == 0)
			{
				myfile1.close();
				remove("save/save1/Save_Data.txt");
			}
			if (selection == 1)
			{
				myfile2.close();
				remove("save/save2/Save_Data.txt");
			}
			if (selection == 2)
			{
				myfile3.close();
				remove("save/save3/Save_Data.txt");
			}
			if (selection == 3)
			{
				myfile4.close();
				remove("save/save4/Save_Data.txt");
			}
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental trigger s
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
		//bSomethingHappened = false;
	}

}

bool checkFile(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}