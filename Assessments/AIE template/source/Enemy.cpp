#include "Enemy.h"
#include "AIE.h"
#include <cstdlib>

Enemy::Enemy()
{
	m_texture = CreateSprite("./images/ship2 24w13h.png", 96, 52, false);

	m_x = rand() % (640 - 96);
	m_y = 780 + 52;

	m_shotCooldown = 0.0f;
	m_shotResetTime = 2.5f;

	m_health = 1;

	m_width = 96;
	m_height = 52;

	m_alive  = true;
}

void Enemy::Update(float dt)
{
	m_y -= 180 * dt;

	m_shotCooldown -= dt;

}

bool Enemy::Fire()
{
	if (m_shotCooldown < 0.0f)
	{
		m_shotCooldown = m_shotResetTime;
		return true;
	}
}


Enemy::~Enemy()
{

}