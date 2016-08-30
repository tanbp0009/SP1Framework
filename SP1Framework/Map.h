#pragma once
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void GetNewMap(std::string filelocation, int InSaveFileNo);
void SetMap();
void loadLevel();
void savelevel(int Inlevel, std::string filedir);
void GetSavedMap(int Inlevel, std::string filedir);
void NewLevel(int InSaveFileNo);
void getfog(int Inlevel);