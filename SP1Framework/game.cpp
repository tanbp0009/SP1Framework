// This is the main file for the game logic and function
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

int level;
int gmmc;
int ggoc;
int ws;
int oldlevel;

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
	numberOfChar = 0;
	nameActive = false;
	nameBounceTime = 0;
	name = "          ";
	level = 0;
	g_sChar.lives = 3;
	gmmc = 0;
	ggoc = 0;
	ws = 0;
	g_sChar.playerdir = '^';
	g_sChar.keys = 0;
	g_sEnemy.m_bActive = false;
	g_dEnemyBounceTime = 0;
	g_dEnemyDamageTime = 0;
	g_sEnemy.m_cLocation.X = 40;
	g_sEnemy.m_cLocation.Y = 1;

    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
	if (g_eGameState == S_GAMEOVER)
	{
		level = 15;
	}
	else
	{
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
		case S_BLACKROOM: gameplay();
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
		break;
	case S_GAMEOVER: renderGameOver();
		break;
	case S_MAINMENU: renderMainMenu();
		break;
	case S_TITLE: renderTitle();
		break;
	case S_INVENTORY: renderInventory();
		break;
	case S_INSTRUCTION: renderInstruction();
		break;
	case S_WIN: renderWin();
		break;
	case S_NAME: enterName();
		break;
	case S_LOADSAVE: renderSaveFile();
		break;
	}
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_LOADLEVEL;
}

void gameplay()            // gameplay logic
{
	if (level == 15)
	{
		enemyPathing();
		enemyCollision();
	}
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
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
			if (ice_check() == false)
			{
				movement_interaction();
			}
			else
			{
				ice_movement_loop();
			}
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		g_sChar.playerdir = '<';
		if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == ' ' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '#' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '°' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '/' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '0')
		{
			//Beep(1440, 30);
			if (ice_check() == false)
			{
				movement_interaction();
			}
			else
			{
				ice_movement_loop();
			}
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		g_sChar.playerdir = 'v';
		if (mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == ' ' || mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '#' || mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '°' || mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '/' || mapCurrent[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '0')
		{
			//Beep(1440, 30);
			if (ice_check() == false)
			{
				movement_interaction();
			}
			else
			{
				ice_movement_loop();
			}
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		g_sChar.playerdir = '>';
		if (mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == ' ' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '#' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '°' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '/' || mapCurrent[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '0')
		{
			//Beep(1440, 30);
			if (ice_check() == false)
			{
				movement_interaction();
			}
			else
			{
				ice_movement_loop();
			}
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
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
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
		savelevel(level);
		if (level == 3 || level == 2)
		{
			level = oldlevel;
		}
		saveChar(g_sChar);
		g_bQuitGame = true;
	}
	if (g_abKeyPressed[K_I] && level != 2 && level != 3)
	{
		savelevel(level);
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
		savelevel(level);
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
	renderitems();
	processUserInput();
}

void renderMainMenu()
{
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
	switch (gmmc)
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
			gmmc = 0;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			gmmc = 1;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			NewLevel();
			bSomethingHappened = true;
			level = 5;
			g_eGameState = S_LOADLEVEL;
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
			gmmc = 0;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			gmmc = 2;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			level = 6;
			//g_sChar = loadChar(g_sChar);
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
			gmmc = 1;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			gmmc = 3;
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
			gmmc = 2;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			gmmc = 3;
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
	score << "Score : " << g_dElapsedTime << 's';
	COORD c = g_Console.getConsoleSize();
	SetMap();
	c.Y = 22;
	c.X = c.X / 2 + 11;
	g_Console.writeToBuffer(c, score.str(), 0x03);
	c.Y = 16;
	g_Console.writeToBuffer(c, "Continue?", 0x03);
	c.X = c.X / 2 + 25;
	c.Y += 2;
	if (g_abKeyPressed[K_LEFT])
		ggoc = 0;
	else if (g_abKeyPressed[K_RIGHT])
		ggoc = 1;
	switch (ggoc)
	{
	case 0:
		g_Console.writeToBuffer(c, yes, 0x06);
		c.X = c.X / 2 + 32;
		g_Console.writeToBuffer(c, Menu[1], 0x07);
		if (g_abKeyPressed[K_SPACE])
		{
			NewLevel();
			init();
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

void renderTitle()
{
	SetMap();
	if (g_dElapsedTime > 6.0) // wait for 3 seconds to switch to game mode, else do nothing
	{
		level = 1;
		g_eGameState = S_LOADLEVEL;
	}
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x07);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x07);
}

void renderGame()
{
    //renderMap();        // renders the map to the buffer first
	SetMap();
	if (level == 15)
	{
		renderEnemy();
	}
    renderCharacter();  // renders the character into the buffer
	renderLives();
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
    c.X = g_Console.getConsoleSize().X - 10;
    c.Y = 1;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << "Elapsed time : " << g_dElapsedTime << "secs";
    c.X = 1;
    c.Y = 1;
    g_Console.writeToBuffer(c, ss.str());
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
		ss << " Û";
	}
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x84);
}

void renderitems()
{
	std::ostringstream ss;
	COORD c;
	ss.str("");
	ss << std::fixed << std::setprecision(3);
	ss << g_sChar.keys << "x key(s)";
	c.X = g_Console.getConsoleSize().X - 43;
	c.Y = 7;
	g_Console.writeToBuffer(c, ss.str());
}
void renderInstruction()
{
	SetMap();
	renderFramerate();
	processUserInput();
}

void renderWin()
{
	bool bSomethingHappened = false;
	std::string Menu[2] = { " Yes ", " No " };
	std::string no = { "<No>" };
	std::string yes = { "<Yes>" };
	std::stringstream score;
	COORD c = g_Console.getConsoleSize();
	SetMap();
	c.Y = 10;
	c.X = 62;
	g_Console.writeToBuffer(c, score.str(), 0x03);
	c.Y = 16;
	g_Console.writeToBuffer(c, "Restart?", 0x03);
	c.Y += 4;
	c.X = 68;
	if (g_abKeyPressed[K_LEFT])
		ws = 0;
	else if (g_abKeyPressed[K_RIGHT])
		ws = 1;
	switch (ws)
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
			NewLevel();
			init();
			g_eGameState = S_MAINMENU;
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, no, 0x07);
		c.X = 60;
		g_Console.writeToBuffer(c, Menu[0], 0x06);
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