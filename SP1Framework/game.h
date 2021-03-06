#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Map.h"
#include "InteractiveObjects.h"
#include "walkover.h"
#include "ice.h"
#include "charData.h"
#include "Enemy.h"
#include "name.h"
#include <Windows.h>

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;


// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
	K_2,
	K_1,
	K_I,
    K_COUNT,
	K_H,
	K_B,
	K_C
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_MAINMENU,
	S_LOADLEVEL,
	S_GAMEOVER,
	S_INVENTORY,
	S_COUNT,
	S_INSTRUCTION,
	S_WIN,
	S_NAME,
	S_LOADSAVE,
};

// struct for the game character
struct SGameChar
{
	std::string name;
    COORD m_cLocation;
    bool  m_bActive;
	char playerdir;
	int lives;
	int keys;
	int relic_scepter;
	int relic_amulet;
	int relic_tablet;
	int relic_ankh;
	int relic_goblet;
	int relic_scarab;
	int currentlevel;
	int score;
};



void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders frame rate
void renderElapsedtime();	// renders elapsed time
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void losegame();
void renderMainMenu();
void GameOver();
void renderGameOver();
void renderInventory();
void renderLives();
void renderitems();
void renderInstruction();
void renderWin();
void enterName();
void renderRoomInfo(int level);

#endif // _GAME_H