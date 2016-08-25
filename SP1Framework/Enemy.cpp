#include "Enemy.h"

double g_dEnemyBounceTime;
double g_dEnemyDamageTime;
SGameEnemy g_sEnemy;

extern SGameChar g_sChar;
extern double g_dElapsedTime;
extern Console g_Console;

void enemyPathing()
{
	if (g_dEnemyBounceTime < g_dElapsedTime)
	{
		if (g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y <= 5 &&
			g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y >= -5 &&
			g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X <= 5 &&
			g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X >= -5)
		{
			if (g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y < 5 && g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y > 0)
			{
				g_sEnemy.m_cLocation.Y++;
				g_sEnemy.m_bActive = false;
			}
			if (g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y > -5  && g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y < 0)
			{
				g_sEnemy.m_cLocation.Y--;
				g_sEnemy.m_bActive = false;
			}
			if (g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X < 5 && g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X > 0)
			{
				g_sEnemy.m_cLocation.X++;
				g_sEnemy.m_bActive = false;
			}
			if (g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X > -5 && g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X < 0)
			{
				g_sEnemy.m_cLocation.X--;
				g_sEnemy.m_bActive = false;
			}
		}
	}
	if (g_sEnemy.m_bActive == false)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dEnemyBounceTime = g_dElapsedTime + 0.3; // 125ms should be enough
		g_sEnemy.m_bActive = true;
	}
}

void renderEnemy()
{
	g_Console.writeToBuffer(g_sEnemy.m_cLocation, '™', 0x0C);
}

void enemyCollision()
{
	if (g_sChar.m_cLocation.X == g_sEnemy.m_cLocation.X && g_sChar.m_cLocation.Y == g_sEnemy.m_cLocation.Y && g_dEnemyDamageTime < g_dElapsedTime)
	{
		g_sChar.lives--;
		g_dEnemyDamageTime = g_dElapsedTime + 0.3; // 125ms should be enough
		g_sEnemy.m_bActive = true;
	}
}