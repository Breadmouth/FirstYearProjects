#include "Entity.h"
#include "AIE.h"

Entity::Entity()
{

}

void Entity::Draw()
{
	MoveSprite(m_texture, m_x, m_y);
   	DrawSprite(m_texture);
}

float Entity::GetX()
{
	return m_x;
}

float Entity::GetY()
{
	return m_y;
}

int Entity::GetWidth()
{
	return m_width;
}

int Entity::GetHeight()
{
	return m_height;
}

void Entity::SetAlive(bool alive)
{
	m_alive = alive;
}

bool Entity::GetAlive()
{
	return m_alive;
}