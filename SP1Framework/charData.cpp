#include "charData.h"
extern int level;
extern Console g_Console;
extern int selection;
extern double g_dBounceTime;
extern double g_dElapsedTime;
extern bool g_abKeyPressed[K_COUNT];

void saveChar(struct SGameChar g_sChar)
{
	std::ofstream myfile("save/Save_Data.txt");
	if (myfile.is_open())
	{
		myfile << g_sChar.name << "\n";
		myfile << g_sChar.playerdir << "\n";
		myfile << g_sChar.m_cLocation.Y << "\n";
		myfile << g_sChar.m_cLocation.X << "\n";
		myfile << g_sChar.lives << "\n";
		myfile << g_sChar.keys << "\n";
		myfile << level << "\n";
		myfile.close();
	}
}

struct SGameChar loadChar(struct SGameChar g_sChar)
{
	std::string line;
	std::ifstream myfile("save/Save_Data.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		g_sChar.name = line;
		getline(myfile, line);
		g_sChar.playerdir = line[0];
		getline(myfile, line);
		g_sChar.m_cLocation.Y = std::stoi(line);
		getline(myfile, line);
		g_sChar.m_cLocation.X = std::stoi(line);
		getline(myfile, line);
		g_sChar.lives = std::stoi(line);
		getline(myfile, line);
		g_sChar.keys = std::stoi(line);
		getline(myfile, line);
		level = std::stoi(line);
		myfile.close();
	}
	return g_sChar;
}

int getNumberOfSaveFile()
{
	int numberOfSaveFiles = 0;
	std::string filename = "save/Save_Data";
	for (int i = 0; i < 4; i++)
	{
		filename += char(i);
		filename += ".txt";
		if (std::ifstream(filename))
		{
			numberOfSaveFiles++;
		}
	}
	return numberOfSaveFiles;
}

void renderSaveFile()
{
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