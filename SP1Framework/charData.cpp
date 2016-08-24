#include "charData.h"
extern int level;

void saveChar(struct SGameChar g_sChar)
{
	std::ofstream myfile("save/Save_Data.txt");
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
	std::ifstream myfile("save/Save_Data.txt");
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
	g_sChar.m_bActive = true;
	return g_sChar;
}