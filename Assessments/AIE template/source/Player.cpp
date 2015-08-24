#include "player.h"
#include "AIE.h"

Player::Player()
{
	m_texture = CreateSprite("./images/ship 32w19h.png", 128, 76, false);

	m_x = 200;
	m_y = 200;

	m_health = 3;
	m_alive = true;
}

bool Player::Update(float dt)
{
	if (IsKeyDown(KEY_LEFT))
		m_x -= (200 * dt);

	if (IsKeyDown(KEY_RIGHT))
		m_x += (200 * dt);

	if (IsKeyDown(KEY_UP))
		m_y += (200 * dt);

	if (IsKeyDown(KEY_DOWN))
		m_y -= (200 * dt);

	if ( m_x > 512)
		m_x = 512;
	else if ( m_x < 0)
		m_x = 0;
	if ( m_y < 76 )
		m_y = 76;
	else if ( m_y >= 780)
		m_y = 780;

	if (IsKeyDown(KEY_SPACE))
	{
		return true;
	}
	return false;
}

