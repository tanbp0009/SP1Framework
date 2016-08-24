#pragma once
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void GetMap(std::string filelocation, int Inlevel);
void SetMap();
void loadLevel();
void savelevel(int Inlevel);
void GetSavedMap(int Inlevel);
void preloadLevel();
COORD GetCharCoord(char InChar);