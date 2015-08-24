#include "PlayerSpeedy.h"
#include "AIE.h"

PlayerSpeedy::PlayerSpeedy()
	:Player()
{

}

bool PlayerSpeedy::Update(float deltaTime)
{
	m_shotCooldown -= deltaTime;

	if (IsKeyDown(KEY_LEFT))
		m_x -= (250 * deltaTime);

	if (IsKeyDown(KEY_RIGHT))
		m_x += (250 * deltaTime);

	if (IsKeyDown(KEY_UP))
		m_y += (250 * deltaTime);

	if (IsKeyDown(KEY_DOWN))
		m_y -= (250 * deltaTime);

	if ( m_x > 512)
		m_x = 512;
	else if ( m_x < 0)
		m_x = 0;
	if ( m_y < 116 )
		m_y = 116;
	else if ( m_y >= 780)
		m_y = 780;

	if (IsKeyDown(KEY_SPACE) &&  m_shotCooldown < 0.0f)
	{
		m_shotCooldown = m_shotResetTime;
		return true;
	}
	return false;
}
