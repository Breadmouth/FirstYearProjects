#include "EnemyBullet.h"
#include "AIE.h"

EnemyBullet::EnemyBullet(float xPos, float yPos)
{
	m_texture = CreateSprite("./images/red bullet.png", 4, 32, false);

	m_x = xPos;
	m_y = yPos;

	m_width = 4;
	m_height = 32;

	m_alive  = true;
}

void EnemyBullet::Update(float deltaTime)
{
	m_y -= 300 * deltaTime;
}