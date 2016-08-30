#pragma once
#include "game.h"
#include <iostream>
#include <fstream>
#include <string>

void saveChar(struct SGameChar Ing_sChar, std::string filedir);
struct SGameChar loadChar(struct SGameChar Ing_sChar, std::string filedir);
void renderSaveFile(struct SGameChar Ing_sChar);
bool checkFile(const char * fileName);