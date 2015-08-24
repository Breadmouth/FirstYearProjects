#include "Bullet.h"
#include "AIE.h"

Bullet::Bullet(float xPos, float yPos)
{
	m_texture = CreateSprite("./images/blue bullet.png", 4, 32, false);

	m_x = xPos;
	m_y = yPos;

	m_alive = true;

	m_width = 4;
	m_height = 32;
}

void Bullet::Update(float dt)
{
	m_y += 300 * dt;
}