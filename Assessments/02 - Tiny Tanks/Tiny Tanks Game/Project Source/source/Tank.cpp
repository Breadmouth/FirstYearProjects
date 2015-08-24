#include "Tank.h"
#include "Game.h"

Tank::Tank(Game* game, const char* textureName, int width, int height, Vector2 pos, int up, int down, int left, int right)
	: Sprite(game, textureName, width, height)
{
	m_game = game;
	Init();
	LoadTexture(textureName);
	m_width = width;
	m_height = height;
	m_position = pos;
	m_anchor = Vector2(0.5, 0.5);
	if (height > width)
		m_radius = (float)height / 2.0f;
	else
		m_radius = (float)width / 2.0f;

	m_keyLeft = left;
	m_keyRight = right;
	m_keyUp = up;
	m_keyDown = down;
}

void Tank::Update(float deltaTime)
{
	m_previousPosition = m_position;

	if (glfwGetKey(m_game->GetWindow(), m_keyLeft))
	{
		m_rotation -= 0.5f * deltaTime;
	}
	if (glfwGetKey(m_game->GetWindow(), m_keyRight))
	{
		m_rotation += 0.5f * deltaTime;
	}
	if (glfwGetKey(m_game->GetWindow(), m_keyDown))
	{
		m_position -= Vector2( sin(m_rotation), cos(m_rotation)) * 80 * deltaTime;

	}
	if (glfwGetKey(m_game->GetWindow(), m_keyUp))
	{
		m_position += Vector2( sin(m_rotation), cos(m_rotation)) * 80 * deltaTime;
	}
	
	Sprite::Update(deltaTime);
}