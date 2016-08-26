#include "name.h"

double nameBounceTime;
std::string name;
int numberOfChar;
extern double g_dElapsedTime;
bool nameActive;
extern Console g_Console;

void enterName()
{

	COORD c;
	c.Y = 2;
	c.X = 1;
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
	g_Console.writeToBuffer(c, name, 0x0F);
}