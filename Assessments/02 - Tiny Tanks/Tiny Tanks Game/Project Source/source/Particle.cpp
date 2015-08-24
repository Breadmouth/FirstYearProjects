#include "Particle.h"
#include "Game.h"

Particle::Particle(Game* game, const char* textureName, int width, int height)
	: Sprite(game, textureName, width, height)
{
	m_game = game;
	Init();
	LoadTexture(textureName);
	m_width = width;
	m_height = height;
	m_anchor = Vector2(0.5, 0.5);
	m_alive = true;
	m_deathTime = 0.3f;
	Sprite::ApplyTransform();
}

void Particle::Update(float deltaTime)
{
	Sprite::Update(deltaTime);
	AdjustAlpha(m_deathTime * 3.3333f);
	m_deathTime -= deltaTime;
	if (m_deathTime <= 0)
	{
		m_alive = false;
	}
	m_position -= Vector2( sin(m_rotation), cos(m_rotation)) * 140 * deltaTime;
}

bool Particle::GetAlive()	const
{
	return m_alive;
}

void Particle::SetAlive(bool alive)
{
	m_alive = alive;
}