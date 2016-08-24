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
void getfog(int Inlevel);
COORD GetCharCoord(char InChar);