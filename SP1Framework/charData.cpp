#include "charData.h"
extern int level;
extern Console g_Console;

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
	SetMap();

	COORD c;
	c.X = 15;
	c.Y = 12;
	std::ifstream myfile1("save/save1/Save_Data.txt");
	if (myfile1.is_open())
	{
		std::string line;
		getline(myfile1, line);

		g_Console.writeToBuffer(c, line, 0x03);
	}
	else
	{
		g_Console.writeToBuffer(c, "Empty File", 0x03);
	}

	c.X = 55;
	std::ifstream myfile2("save/save2/Save_Data.txt");
	if (myfile2.is_open())
	{
		std::string line;
		getline(myfile2, line);

		g_Console.writeToBuffer(c, line, 0x03);
	}
	else
	{
		g_Console.writeToBuffer(c, "Empty File", 0x03);
	}

	c.X = 15;
	c.Y = 18;
	std::ifstream myfile3("save/save3/Save_Data.txt");
	if (myfile3.is_open())
	{
		std::string line;
		getline(myfile3, line);

		g_Console.writeToBuffer(c, line, 0x03);
	}
	else
	{
		g_Console.writeToBuffer(c, "Empty File", 0x03);
	}

	c.X = 55;
	std::ifstream myfile4("save/save4/Save_Data.txt");
	if (myfile4.is_open())
	{
		std::string line;
		getline(myfile4, line);

		g_Console.writeToBuffer(c, line, 0x03);
	}
	else
	{
		g_Console.writeToBuffer(c, "Empty File", 0x03);
	}
}

bool checkFile(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}