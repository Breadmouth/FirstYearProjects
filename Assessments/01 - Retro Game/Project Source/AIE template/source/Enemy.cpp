#include "Enemy.h"
#include "AIE.h"
#include <cstdlib>

Enemy::Enemy(float velocity)
{
	m_texture = CreateSprite("./images/ship2 24w13h.png", 96, 52, false);
	m_deathTexture1 = CreateSprite("./images/explosion.png", 60, 60, false);
	m_deathTexture2 = CreateSprite("./images/explosion2.png", 60, 60, false);
	m_deathTexture3 = CreateSprite("./images/explosion3.png", 60, 60, false);


	m_x = rand() % (640 - 96);
	m_y = 780 + 52;

	m_shotCooldown = 0.0f;
	m_shotResetTime = 2.5f;

	m_deathTime = 0.3f;

	m_velocity = velocity;

	m_width = 96;
	m_height = 52;
	
	m_health = 1;
	m_alive  = true;

	m_score = 100;
}

void Enemy::Update(float deltaTime)
{
	if (m_alive == true)
	{
	m_y -= m_velocity * deltaTime;

	m_shotCooldown -= deltaTime;
	}

}

bool Enemy::Fire()
{
	if (m_shotCooldown < 0.0f)
	{
		m_shotCooldown = m_shotResetTime;
		return true;
	}
	else
		return false;
}

void Enemy::Die(float deltaTime)
{
	if (m_deathTime > 0.2f)
	{
	MoveSprite(m_deathTexture1, m_x + 18, m_y + 4);
	DrawSprite(m_deathTexture1);
	}
	else if (m_deathTime > 0.1f)
	{
	MoveSprite(m_deathTexture2, m_x + 18, m_y + 4);
	DrawSprite(m_deathTexture2);
	}
	else
	{
	MoveSprite(m_deathTexture3, m_x + 18, m_y + 4);
	DrawSprite(m_deathTexture3);
	}

	m_deathTime -= deltaTime;
	if (m_deathTime <= 0.0f)
	{
		m_delete = true;
	}
}

int Enemy::GetScore()
{
	return m_score;
}

Enemy::~Enemy()
{

}