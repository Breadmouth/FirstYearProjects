#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(Game* game, const char* textureName, int width, int height)
	: Sprite(game, textureName, width, height)
{
	m_game = game;
	Init();
	LoadTexture(textureName);
	m_width = width;
	m_height = height;
	if (height > width)
		m_radius = (float)height / 2.0f;
	else
		m_radius = (float)width / 2.0f;

	m_anchor = Vector2(0.5, 0.5);
	m_alive = true;
}

void Bullet::Update(float deltaTime)
{
	m_position -= Vector2( sin(m_rotation), cos(m_rotation)) * 400 * deltaTime;

	Sprite::Update(deltaTime);
}

void Bullet::FixPosition()
{
	m_position -= Vector2( sin(m_rotation), cos(m_rotation)) * 58;
}

bool Bullet::GetAlive()	const
{
	return m_alive;
}

void Bullet::SetAlive(bool alive)
{
	m_alive = alive;
}