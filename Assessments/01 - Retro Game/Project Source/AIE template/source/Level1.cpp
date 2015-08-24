#include "Level1.h"
#include "AIE.h"

Level1::Level1(unsigned int width, unsigned int height, ScreenManager* sm)
	:Level(width, height, sm)
{
	m_background = CreateSprite("./images/grassland.png", 640, 3200, false); 
}

Level1::~Level1()
{

}

void Level1::AddEnemy(float veloctiy)
{
	if (rand() % 10 >= 8)
	{
	Enemy* newEnemy = new EnemyAdvanced(180);
	m_enemies.push_back(newEnemy);
	}
	else
	{
	Enemy* newEnemy = new Enemy(180);
	m_enemies.push_back(newEnemy);
	}
}