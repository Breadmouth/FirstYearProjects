#include "EnemyBullet.h"
#include "AIE.h"

EnemyBullet::EnemyBullet(float xPos, float yPos)
{
	m_texture = CreateSprite("./images/red bullet.png", 4, 32, false);

	m_x = xPos;
	m_y = yPos;

	m_alive  = true;
}

void EnemyBullet::Update(float dt)
{
	m_y -= 300 * dt;
}