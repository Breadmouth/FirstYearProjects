#include "Level2.h"
#include "AIE.h"

Level2::Level2(unsigned int width, unsigned int height, ScreenManager* sm)
	:Level(width, height, sm)
{
	m_background = CreateSprite("./images/moon.png", 640, 3200, false); 
	m_enemySpawnResetTime = 1.10f;

	m_levelLength = 50.0f;
}

Level2::~Level2()
{

}

void Level2::AddEnemy(float veloctiy)
{
	if (rand() % 10 >= 8)
	{
	Enemy* newEnemy = new EnemyAdvanced(200);
	m_enemies.push_back(newEnemy);
	}
	else
	{
	Enemy* newEnemy = new Enemy(200);
	m_enemies.push_back(newEnemy);
	}
}