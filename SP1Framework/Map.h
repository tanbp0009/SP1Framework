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
void savelevel(int Inlevel, std::string filedir);
void GetSavedMap(int Inlevel, std::string filedir);
void NewLevel();
void getfog(int Inlevel);