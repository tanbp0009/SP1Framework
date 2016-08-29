#include "name.h"

double nameBounceTime;
std::string name;
int numberOfChar;
extern double g_dElapsedTime;
bool nameActive;
extern Console g_Console;
extern int level;
extern EGAMESTATES g_eGameState;

void enterName()
{
	SetMap();
	COORD c = g_Console.getConsoleSize();
	c.Y = 13;
	c.X = c.X / 2 - 9;
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
				name[numberOfChar] = char(i);
				numberOfChar++;
				nameActive = false;
			}
		}
	}
	if (nameActive == false)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		nameBounceTime = g_dElapsedTime + 0.3; // 125ms should be enough
		nameActive = true;
	}
	if (isKeyPressed(VK_RETURN) && numberOfChar != 0)
	{
		NewLevel();
		level = 7;
		g_eGameState = S_LOADLEVEL;
	}
	g_Console.writeToBuffer(c, name, 0x0F);
}