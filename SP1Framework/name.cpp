#include "name.h"

double nameBounceTime;
std::string name;
int numberOfChar;
extern double g_dElapsedTime;
bool nameActive;
extern Console g_Console;
extern int level;
extern EGAMESTATES g_eGameState;
extern SGameChar g_sChar;
extern int playernum;
int i = 65;
void enterName()
{
	SetMap();
	COORD c = g_Console.getConsoleSize();
	c.Y = 13;
	c.X = c.X / 2 - 9;
	nameActive = true;
	if (nameBounceTime < g_dElapsedTime)
	{
		if (isKeyPressed(VK_BACK) && numberOfChar !=0)
		{
			numberOfChar--;
			name[numberOfChar] = ' ';
			
			nameActive = false;
		}
		for (int i = 65; i < 91 && numberOfChar != 10; i++)
		{
			if (isKeyPressed(i))
			{
				name[numberOfChar] = (char)(i);
				numberOfChar++;
				nameActive = false;
				g_Console.writeToBuffer(c, name, 0x0F);
			}

		}
		//if ((detectKeysPressed() > 64) && (detectKeysPressed() < 91))
		//{
		//	name[numberOfChar] = (char)(detectKeysPressed());
		//	numberOfChar++;
		//	nameActive = false;
		//}
	}
	if (nameActive == false)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		nameBounceTime = g_dElapsedTime + 0.3; // 125ms should be enough
	}
	if (isKeyPressed(VK_RETURN) && numberOfChar != 0)
	{
		
		NewLevel(playernum);
		g_sChar = loadChar(g_sChar, std::to_string(playernum));
		level = 7;
		g_sChar.name = name;
		saveChar(g_sChar, std::to_string(playernum));
		
		g_eGameState = S_LOADLEVEL;
	}
	if (isKeyPressed(VK_HOME))
	{
		level = 1;
		g_eGameState = S_LOADLEVEL;
	}
	g_Console.writeToBuffer(c, name, 0x0F);
}

bool newGame()
{
	if (!checkFile("save/save1/Save_Data.txt"))
	{
		playernum = 1;
		return true;
	}
	else  if (!checkFile("save/save2/Save_Data.txt"))
	{
		playernum = 2;
		return true;
	}
	else if (!checkFile("save/save3/Save_Data.txt"))
	{
		playernum = 3;
		return true;
	}
	else if (!checkFile("save/save4/Save_Data.txt"))
	{
		playernum = 4;
		return true;
	}
	else
		return false;
}

int detectKeysPressed()
{
	for (int i = 65; i < 91; i++)
	{
		if (isKeyPressed(i))
		{
			return i;
		}
	}
}