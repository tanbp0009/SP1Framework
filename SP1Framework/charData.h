#pragma once
#include "game.h"
#include <iostream>
#include <fstream>
#include <string>

void saveChar(struct SGameChar g_sChar);
struct SGameChar loadChar(struct SGameChar g_sChar);