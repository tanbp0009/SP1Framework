#pragma once
#include "game.h"
#include <iostream>
#include <fstream>
#include <string>

struct SGameEnemy
{
	COORD m_cLocation;
	bool  m_bActive;
};

void enemyPathing();
void renderEnemy();
void enemyCollision();