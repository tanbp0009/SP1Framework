#include "Enemy.h"

double g_dEnemyBounceTime;
double g_dEnemyDamageTime;
SGameEnemy g_sEnemy;
extern EGAMESTATES g_eGameState;
extern int level;
extern SGameChar g_sChar;
extern double g_dElapsedTime;
extern Console g_Console;

void enemyPathing()
{
	if (g_dEnemyBounceTime < g_dElapsedTime)
	{
		if (g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y <= 8 &&
			g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y >= -8 &&
			g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X <= 8 &&
			g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X >= -8)
		{
			if (g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y <= 8 && g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y > 0)
			{
				g_sEnemy.m_cLocation.Y++;
				g_sEnemy.m_bActive = false;
			}
			if (g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y >= -8  && g_sChar.m_cLocation.Y - g_sEnemy.m_cLocation.Y < 0)
			{
				g_sEnemy.m_cLocation.Y--;
				g_sEnemy.m_bActive = false;
			}
			if (g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X <= 8 && g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X > 0)
			{
				g_sEnemy.m_cLocation.X++;
				g_sEnemy.m_bActive = false;
			}
			if (g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X >= -8 && g_sChar.m_cLocation.X - g_sEnemy.m_cLocation.X < 0)
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
		g_dEnemyDamageTime = g_dElapsedTime + 0.4; // give player damage immunity
		g_sEnemy.m_bActive = true;
		if (g_sChar.lives == 2)
		{
			PlaySound(TEXT("audio/life.wav"), NULL, SND_ASYNC);
		}
		if (g_sChar.lives == 1)
		{
			PlaySound(TEXT("audio/life2.wav"), NULL, SND_ASYNC);
		}
	}
	if (g_sChar.lives == 0)
	{
		PlaySound(TEXT("audio/life3.wav"), NULL, SND_ASYNC);
		level = 19;
		g_eGameState = S_LOADLEVEL;
		PlaySound(TEXT("audio/menu.wav"), NULL, SND_ASYNC);
	}
}