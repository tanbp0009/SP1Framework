#pragma once
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void GetNewMap(std::string filelocation);
void SetMap();
void loadLevel();
void savelevel(int Inlevel);
void GetSavedMap(int Inlevel);
void NewLevel();
//void GetFogMap(int level);
COORD GetCharCoord(char InChar);