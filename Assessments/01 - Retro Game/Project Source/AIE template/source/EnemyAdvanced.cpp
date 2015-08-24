#include "EnemyAdvanced.h"
#include "AIE.h"
#include <cstdlib>

EnemyAdvanced::EnemyAdvanced(float velocity)
	:Enemy(velocity)
{
	m_texture = CreateSprite("./images/ship3 22w21h.png", 88, 84, false);

	m_y = 780 + 84;

	m_width = 88;
	m_height = 84;
	
	m_health = 2;

	m_score = 200;
}

EnemyAdvanced::~EnemyAdvanced()
{

}