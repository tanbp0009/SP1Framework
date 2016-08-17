#pragma once
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void GetMap(std::string Inlevel);
void SetMap();
void loadLevel();
void savelevel(int Inlevel);
void GetSavedMap(int Inlevel);