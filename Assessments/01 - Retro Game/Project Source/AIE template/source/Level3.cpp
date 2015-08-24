#include "Level3.h"
#include "AIE.h"

Level3::Level3(unsigned int width, unsigned int height, ScreenManager* sm)
	:Level(width, height, sm)
{
	m_background = CreateSprite("./images/PurplePlanet.png", 640, 3200, false); 
	m_enemySpawnResetTime = 0.90f;

	m_levelLength = 60.0f;
}

Level3::~Level3()
{

}

void Level3::AddEnemy(float veloctiy)
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