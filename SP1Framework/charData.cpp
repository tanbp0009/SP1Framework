#include "charData.h"
extern int level;

void saveChar(struct SGameChar g_sChar)
{
	std::ofstream myfile("save/Save_Data1.txt");
	if (myfile.is_open())
	{
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
	std::ifstream myfile("save/Save_Data1.txt");
	if (myfile.is_open())
	{
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