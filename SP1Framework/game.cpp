﻿// This is the main file for the game logic and function
//
//
#include "game.h"
#include "walkover.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "ice.h"
#include "name.h"

int info;
int level;
int selection;
int oldlevel;
int playernum;
bool dialogFlag = false;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(80, 25, "SP1 Framework");

extern char mapCurrent[25][80];
extern SGameEnemy g_sEnemy;
extern double g_dEnemyBounceTime;
extern double g_dEnemyDamageTime;
extern double nameBounceTime;
extern bool nameActive;
extern std::string name;
extern int numberOfChar;
//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
	info = 0;
	playernum = 1;
	numberOfChar = 0;
	nameActive = false;
	nameBounceTime = 0;
	name = "          ";
	level = 0;
	g_sChar.lives = 3;
	selection = 0;
	g_sChar.playerdir = '^';
	g_sChar.keys = 0;
	g_sChar.relic_scepter = 0; // 50 points per
	g_sChar.relic_amulet = 0; // 100 points per
	g_sChar.relic_tablet = 0; // 150 points per
	g_sChar.relic_ankh = 0; // 200 points per
	g_sChar.relic_goblet = 0; // 250 points per
	g_sChar.relic_scarab = 0; // 300 points per
	g_sEnemy.m_bActive = false;
	g_dEnemyBounceTime = 0;
	g_dEnemyDamageTime = 0;
	g_sEnemy.m_cLocation.X = 40;
	g_sEnemy.m_cLocation.Y = 1;
	g_sChar.score = 0;

    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
	if (g_eGameState == S_GAMEOVER)
	{
		PlaySound(TEXT("audio/menu.wav"), NULL, SND_ASYNC);
		level = 7;
	}
	else
	{
		PlaySound(TEXT("audio/menu.wav"), NULL, SND_ASYNC);
		g_eGameState = S_SPLASHSCREEN;
	}
    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 18, L"Raster");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_2] = isKeyPressed('2');
	g_abKeyPressed[K_1] = isKeyPressed('1');
	g_abKeyPressed[K_I] = isKeyPressed(73);
	g_abKeyPressed[K_H] = isKeyPressed(72);
	g_abKeyPressed[K_B] = isKeyPressed(66);
	g_abKeyPressed[K_C] = isKeyPressed(67);

}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
	if (g_eGameState != S_GAMEOVER)
	{
		g_dElapsedTime += dt;
		g_dDeltaTime = dt;
	}
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------

void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_GAME: renderGame();
		break;
	case S_LOADLEVEL: loadLevel();
		dialogFlag = false;
		break;
	case S_GAMEOVER: renderGameOver();
		break;
	case S_MAINMENU: renderMainMenu();
		break;
	case S_INVENTORY: renderInventory();
		break;
	case S_INSTRUCTION: renderInstruction();
		break;
	case S_WIN: renderWin();
		break;
	case S_NAME: enterName();
		renderFramerate();
		break;
	case S_LOADSAVE: renderSaveFile(g_sChar);
		break;
	}
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime < 0.1)
	{
		g_eGameState = S_LOADLEVEL;
	}
	if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
	{
		level = 1;
		g_eGameState = S_LOADLEVEL;
	}
}

void gameplay()            // gameplay logic
{
	if (level == 15)
	{
		enemyPathing();
		enemyCollision();
	}
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	ice_check();
	if (ice_check() == true)
	{
		ice_movement_loop();
	}
	else if (ice_check() == false)
	{
		moveCharacter();    // moves the character, collision detection, physics, etc
		// sound can be played here too.
	}
}
void renderRoomInfo(int level)
{
	bool bSomethingHappened = false;
	std::string infostring[2] {"Press 'c' to close", ""};
	COORD c = g_Console.getConsoleSize();
	c.X = 1;
	c.Y = 1;
	if (isKeyPressed(67))
	{
		bSomethingHappened = true;
		info = 1;
		dialogFlag = true;
	}

	if (dialogFlag == false)
	{
		std::string infostringborder[1]{"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛPress 'c' to closeÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"};
		std::string infostring1[4]{"This pyramid is pretty dark, I should get that torch '§'.", "Those pieces of ruins might be worth a forturne, I should take some of it.", "Damn those spikes '#' look like they will hurt alot... I better avoid those.", "(Press space to interact)"};
		std::string infostring2[3]{"Oh, is that a button 'o'? Pushing buttons is gonna do something right?        ", "Perhaps it opens a door ')'?                                                  ", "(Press space to push buttons)                                                 "};
		std::string infostring3[3]{"Wha... What is that... Is that a teleporter 'è'?                              ", "I wonder where it will lead me to.                                            "};
		std::string infostring4[4]{"I must me getting closer to the treasure, I need to keep pressing on.         ", "The north door 'D' has three locks, I wonder where the keys 'Ÿ' are.          ", "Hmmm... the other rooms might contain the keys.                               ", "I should avoid that red guy '™' over there... he looks scary.                 "};
		std::string infostring5[1]{"If I want to get that key I i'll have to get through this maze.               "};
		std::string infostring6[2]{"These boulders 'ê' looks light enough to be pushed,                           ", "lets put my training to the test!                                            "};
		std::string infostring7[2]{"The floors here look slippery, it will be wise for me to watch my step.       ", "That looks like a medkit '¤', that would heal my wounds.                     "};
		std::string infostring8[2]{"The treasure 'ß' is in this room, i just need to figure out how to get to it. "};

		if (level == 7)
		{
			switch (info)
			{
			case 0:
			{
					  g_Console.writeToBuffer(c, infostring1[0], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostring1[1], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostring1[2], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostring1[3], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostringborder[0], 0x08);
			}
			case 1:;
			}
		}
		if (level == 9)
		{
			switch (info)
			{
			case 0:
			{
					  g_Console.writeToBuffer(c, infostring2[0], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostring2[1], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostring2[2], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostringborder[0], 0x08);
			}
			case 1:;
			}
		}
		if (level == 11)
		{
			switch (info)
			{
			case 0:;
				g_Console.writeToBuffer(c, infostring3[0], 0x07);
				c.Y += 1;
				g_Console.writeToBuffer(c, infostring3[1], 0x07);
				c.Y += 1;
				g_Console.writeToBuffer(c, infostringborder[0], 0x08);
			case 1:;
			}
		}
		if (level == 15)
		{
			c.Y = 3;
			switch (info)
			{
			case 0:
			{
					  if (g_sChar.keys == 0)
					  {
						  g_Console.writeToBuffer(c, infostringborder[0], 0x08);
						  c.Y += 1;
						  g_Console.writeToBuffer(c, infostring4[0], 0x0F);
						  c.Y += 1;
						  g_Console.writeToBuffer(c, infostring4[1], 0x0F);
						  c.Y += 1;
						  g_Console.writeToBuffer(c, infostring4[2], 0x0F);
						  c.Y += 1;
						  g_Console.writeToBuffer(c, infostring4[3], 0x0F);
						  c.Y += 1;
						  g_Console.writeToBuffer(c, infostringborder[0], 0x08);
					  }
			}
			case 1:;
			}
		}
		if (level == 14)
		{
			switch (info)
			{
			case 0:
			{
					  g_Console.writeToBuffer(c, infostring5[0], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostringborder[0], 0x08);
			}
			case 1:;
			}
		}
		if (level == 16)
		{
			switch (info)
			{
			case 0:
			{
					  g_Console.writeToBuffer(c, infostring7[0], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostring7[1], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostringborder[0], 0x08);
			}
			case 1:;
			}
		}
		if (level == 17)
		{
			switch (info)
			{
			case 0:
			{
					  g_Console.writeToBuffer(c, infostring6[0], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostring6[1], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostringborder[0], 0x08);
			}

			case 1:;
			}
		}
		if (level == 18)
		{
			switch (info)
			{
			case 0:
			{
					  g_Console.writeToBuffer(c, infostring8[0], 0x0F);
					  c.Y += 1;
					  g_Console.writeToBuffer(c, infostringborder[0], 0x08);
			}
			case 1:;
			}
		}
	}
}
void moveCharacter()
{
    bool bSomethingHappened = false; 
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
	{
		g_sChar.playerdir = '^';
		if (mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == ' ' || mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == '#' || mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == '°' || mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == '/' || mapCurrent[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == '0')
		{
			//Beep(1440, 30);
			movement_interaction();
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		g_sChar.playerdir = '<';
		if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == ' ' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '#' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '°' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '/' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '0')
		{
			//Beep(1440, 30);
			movement_interaction();
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		g_sChar.playerdir = 'v';
		if (mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == ' ' || mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '#' || mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '°' || mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '/' || mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '0')
		{
			//Beep(1440, 30);
			movement_interaction();
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		g_sChar.playerdir = '>';
		if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == ' ' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '#' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '°' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '/' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '0')
		{
			//Beep(1440, 30);
			movement_interaction();
			bSomethingHappened = true;
		}
	}
    if (g_abKeyPressed[K_SPACE])
    {
		interactobjectinfront();
        bSomethingHappened = true;
    }
    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.150; // 125ms should be enough
    }
}
void processUserInput()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	
    // quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
	{
		savelevel(level, std::to_string(playernum));
		if (level == 3 || level == 2)
		{
			level = oldlevel;
		}
		saveChar(g_sChar, std::to_string(playernum));
		g_bQuitGame = true;
	}
	if (g_abKeyPressed[K_I] && level != 2 && level != 3)
	{
		savelevel(level, std::to_string(playernum));
		oldlevel = level;
		level = 2;
		g_eGameState = S_LOADLEVEL;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_I])
	{
		level = oldlevel;
		g_eGameState = S_LOADLEVEL;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_H] && level != 3 && level !=2)
	{
		savelevel(level, std::to_string(playernum));
		oldlevel = level;
		level = 3;
		g_eGameState = S_LOADLEVEL;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_H])
	{
		level = oldlevel;
		g_eGameState = S_LOADLEVEL;
		bSomethingHappened = true;
	}
	if (isKeyPressed(VK_HOME))
	{
		saveChar(g_sChar, std::to_string(playernum));
		savelevel(level, std::to_string(playernum));
		level = 1;
		g_eGameState = S_LOADLEVEL;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x0F);
}

void renderInventory()
{
	SetMap();
	renderFramerate();
	renderElapsedtime();
	renderitems();
	processUserInput();
}

void renderMainMenu()
{
	level = 1;
	bool bSomethingHappened = false;
	std::string Menu[4] = { " Start New Adventure ", " Continue Old Adventure " , " Instructions " ,  " Exit " };
	std::string arrow[4] = { "<Start New Adventure>", "<Continue Old Adventure>", "<Instructions>", "<Exit>" };
	COORD c = g_Console.getConsoleSize();
	SetMap();
	c.Y = 16;
	c.X = c.X / 2 - 11;
	g_Console.writeToBuffer(c, "Press <Space> to Select:", 0x03);
	c.X = c.X / 2 + 16;
	c.Y += 2;
	switch (selection)
	{
	case 0:
		g_Console.writeToBuffer(c, arrow[0], 0x06);
		c.Y += 1;
		c.X = c.X / 2 + 13;
		g_Console.writeToBuffer(c, Menu[1], 0x07);
		c.Y += 1;
		c.X = c.X / 2 + 19;
		g_Console.writeToBuffer(c, Menu[2], 0x07);
		c.Y += 1;
		c.X = c.X / 2 + 21;
		g_Console.writeToBuffer(c, Menu[3], 0x07);
		if (g_dBounceTime > g_dElapsedTime)
		{
			return;
		}
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			selection = 0;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			selection = 1;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			bSomethingHappened = true;
			if (newGame() == true)
			{
				level = 5;
				g_eGameState = S_LOADLEVEL;
			}
			else
				g_Console.writeToBuffer(5, 5, "No character slots available", 0x07);
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, Menu[0], 0x07);
		c.Y += 1;
		c.X = c.X / 2 + 13;
		g_Console.writeToBuffer(c, arrow[1], 0x06);
		c.Y += 1;
		c.X = c.X / 2 + 19;
		g_Console.writeToBuffer(c, Menu[2], 0x07);
		c.Y += 1;
		c.X = c.X / 2 + 21;
		g_Console.writeToBuffer(c, Menu[3], 0x07);
		if (g_dBounceTime > g_dElapsedTime)
		{
			return;
		}
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			selection = 0;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			selection = 2;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			level = 6;
			bSomethingHappened = true;
			g_eGameState = S_LOADLEVEL;
		}
		break;
	case 2:
		g_Console.writeToBuffer(c, Menu[0], 0x07);
		c.Y += 1;
		c.X = c.X / 2 + 13;
		g_Console.writeToBuffer(c, Menu[1], 0x07);
		c.Y += 1;
		c.X = c.X / 2 + 19;
		g_Console.writeToBuffer(c, arrow[2], 0x06);
		c.Y += 1;
		c.X = c.X / 2 + 21;
		g_Console.writeToBuffer(c, Menu[3], 0x07);
		if (g_dBounceTime > g_dElapsedTime)
		{
			return;
		}
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			selection = 1;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			selection = 3;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			bSomethingHappened = true;
			level = 3;
			g_eGameState = S_LOADLEVEL;
		}
		break;
	case 3:
		g_Console.writeToBuffer(c, Menu[0], 0x07);
		c.Y += 1;
		c.X = c.X / 2 + 13;
		g_Console.writeToBuffer(c, Menu[1], 0x07);
		c.Y += 1;
		c.X = c.X / 2 + 19;
		g_Console.writeToBuffer(c, Menu[2], 0x07);
		c.Y += 1;
		c.X = c.X / 2 + 21;
		g_Console.writeToBuffer(c, arrow[3], 0x06);
		if (g_dBounceTime > g_dElapsedTime)
		{
			return;
		}
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			selection = 2;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			selection = 3;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			bSomethingHappened = true;
			g_bQuitGame = true;
			// exit game.
		}
		break;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
		//bSomethingHappened = false;
	}
}

void renderGameOver()
{
	std::string Menu[2] = { " Yes ", " No " };
	std::string no = { "<No>" };
	std::string yes = { "<Yes>" };
	std::stringstream score;
	score.str() = "";
	score << "Score : " << g_sChar.score << " point(s)";
	COORD c = g_Console.getConsoleSize();
	SetMap();
	c.Y = 22;
	c.X = c.X / 2 + 5;
	g_Console.writeToBuffer(c, score.str(), 0x03);
	c.X = c.X + 5;
	c.Y = 16;
	g_Console.writeToBuffer(c, "Continue?", 0x03);
	c.X -= 1;
	c.X = c.X / 2 + 25;
	c.Y += 2;
	if (g_abKeyPressed[K_LEFT])
		selection = 0;
	else if (g_abKeyPressed[K_RIGHT])
		selection = 1;
	switch (selection)
	{
	case 0:
		g_Console.writeToBuffer(c, yes, 0x06);
		c.X = c.X / 2 + 32;
		g_Console.writeToBuffer(c, Menu[1], 0x07);
		if (g_abKeyPressed[K_SPACE])
		{
			NewLevel(playernum);
			init();
			saveChar(g_sChar, std::to_string(playernum));
			g_eGameState = S_LOADLEVEL;
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, Menu[0], 0x07);
		c.X = c.X / 2 + 32;
		g_Console.writeToBuffer(c, no, 0x06);
		if (g_abKeyPressed[K_SPACE])
			g_bQuitGame = true;
		break;
	}

}

void renderSplashScreen()  // renders the splash screen
{
	SetMap();
	
	if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
	{
		level = 1;
		g_eGameState = S_LOADLEVEL;
	}
}

void renderGame()
{
    //renderMap();        // renders the map to the buffer first
	SetMap();
	if (level == 15)
	{
		renderEnemy();
	}
    
	renderElapsedtime();
	renderLives();
	renderCharacter();  // renders the character into the buffer
	renderRoomInfo(level);
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0A;

    g_Console.writeToBuffer(g_sChar.m_cLocation, g_sChar.playerdir, charColor);
}

void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x87);
}
void renderElapsedtime()
{
	COORD c;
    // displays the elapsed time
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
    ss.str("");
    ss << "Time : " << g_dElapsedTime << "secs";
	c.X = g_Console.getConsoleSize().X - 18;
	c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x87);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}
void renderLives()
{
	COORD c;
	std::ostringstream ss;
	ss.str("");
	ss << std::fixed << std::setprecision(3);
	ss << "Lives :";
	for (int i = 0; i < g_sChar.lives; i++)
	{
		ss << (char)3;
	}
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x8C);
}

void renderitems()
{
	std::ostringstream ss, sa, sb, sc, sd, se, sf;
	COORD c;
	ss.str("");
	sa.str("");
	sb.str("");
	sc.str("");
	sd.str("");
	se.str("");
	sf.str("");
	c.X = g_Console.getConsoleSize().X / 2 - 5;
	c.Y = 7;
	ss << g_sChar.keys << "x key(s)";
	g_Console.writeToBuffer(c, ss.str());
	c.Y += 2;
	sa << g_sChar.relic_scepter << "x scepter piece(s)";
	g_Console.writeToBuffer(c, sa.str());
	c.Y += 2;
	sb << g_sChar.relic_amulet << "x amulet piece(s)";
	g_Console.writeToBuffer(c, sb.str());
	c.Y += 2;
	sc << g_sChar.relic_tablet << "x tablet piece(s)";
	g_Console.writeToBuffer(c, sc.str());
	c.Y += 2;
	sd << g_sChar.relic_ankh << "x ankh piece(s)";
	g_Console.writeToBuffer(c, sd.str());
	c.Y += 2;
	se << g_sChar.relic_goblet << "x goblet piece(s)";
	g_Console.writeToBuffer(c, se.str());
	c.Y += 2;
	sf << g_sChar.relic_scarab << "x scarab piece(s)";
	g_Console.writeToBuffer(c, sf.str());

}
void renderInstruction()
{
	SetMap();
	renderFramerate();
	renderElapsedtime();
	processUserInput();
}

void renderWin()
{
	bool bSomethingHappened = false;
	std::string Menu[2] = { " Yes ", " No " };
	std::string no = { "<No>" };
	std::string yes = { "<Yes>" };
	std::stringstream score;
	score.str() = "";
	score << "Score : " << g_sChar.score << " point(s)";
	COORD c;
	SetMap();
	c.Y = 10;
	c.X = 57;
	g_Console.writeToBuffer(c, score.str(), 0x03);
	c.Y = 16;
	c.X += 5;
	g_Console.writeToBuffer(c, "Restart?", 0x03);
	c.Y += 4;
	c.X = 68;
	if (g_abKeyPressed[K_LEFT])
		selection = 0;
	else if (g_abKeyPressed[K_RIGHT])
		selection = 1;
	switch (selection)
	{
	case 0:
		g_Console.writeToBuffer(c, Menu[1], 0x07);
		c.X = 60;
		g_Console.writeToBuffer(c, yes, 0x06);
		if (g_dBounceTime > g_dElapsedTime)
		{
			return;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			NewLevel(playernum);
			init();
			g_eGameState = S_MAINMENU;
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, no, 0x06);
		c.X = 60;
		g_Console.writeToBuffer(c, Menu[0], 0x07);
		if (g_dBounceTime > g_dElapsedTime)
		{
			return;
		}
		if (g_abKeyPressed[K_SPACE])
			g_bQuitGame = true;
		break;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
		//bSomethingHappened = false;
	}
}
