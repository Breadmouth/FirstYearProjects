#include "Player.h"
#include "AIE.h"

Player::Player()
{
	m_width = 128;
	m_height = 76;

	m_texture = CreateSprite("./images/ship 32w19h.png", m_width, m_height, false);
	m_propulsion1 = CreateSprite("./images/propulsion.png", 18, 21, false);
	m_propulsion2 = CreateSprite("./images/propulsion2.png", 18, 21, false);
	m_propulsion3 = CreateSprite("./images/propulsion3.png", 18, 21, false);

	m_propulsionReset = 0.4f;

	m_x = 256;
	m_y = 200;

	m_health = 3;
	m_alive = true;

	m_shotCooldown = 0.0f;
	m_shotResetTime = 0.50f;
}

void Player::DrawPropulsion(float deltaTime)
{
	m_propulsionReset -= deltaTime;

	if (m_propulsionReset > 0.3f)
	{
		MoveSprite(m_propulsion1, m_x + 55, m_y - m_height);
		DrawSprite(m_propulsion1);
	}
	else if (m_propulsionReset > 0.2f)
	{
		MoveSprite(m_propulsion2, m_x + 55, m_y - m_height);
		DrawSprite(m_propulsion2);
	}
	else if (m_propulsionReset > 0.1f)
	{	MoveSprite(m_propulsion3, m_x + 55, m_y - m_height);
		DrawSprite(m_propulsion3);

	}
	else if (m_propulsionReset > 0.0f)
	{
		MoveSprite(m_propulsion2, m_x + 55, m_y - m_height);
		DrawSprite(m_propulsion2);
	}
	else
	{
		MoveSprite(m_propulsion1, m_x + 55, m_y - m_height);
		DrawSprite(m_propulsion1);
		m_propulsionReset = 0.4f;
	}
}

void Player::Reset()
{
	m_x = 256;
	m_y = 200;

	m_health = 3;
	m_alive = true;

	m_shotCooldown = 0.0f;
}