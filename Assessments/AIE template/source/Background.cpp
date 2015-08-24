#include "Background.h"
#include "AIE.h"

Background::Background()
{
	m_texture = CreateSprite("./images/grassland.png", 640, 3200, false);

	m_image1Y = 3200.0f;
	m_image2Y = 6399.0f;
}

void Background::Scroll(float dt)
{
	m_image1Y -= (150 * dt);

	MoveSprite(m_texture, 0, m_image1Y);
	DrawSprite(m_texture);

	m_image2Y -= (150 * dt);

	MoveSprite(m_texture, 0, m_image2Y);
	DrawSprite(m_texture);

	if (m_image1Y <= 0)
	{
		m_image1Y = 3200;
		m_image2Y = 6399;
	}
}
