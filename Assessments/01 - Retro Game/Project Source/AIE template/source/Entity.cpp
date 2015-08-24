#include "Entity.h"
#include "AIE.h"

Entity::Entity()
{
	m_delete = false;
}

void Entity::Draw()
{
	MoveSprite(m_texture, m_x, m_y);
   	DrawSprite(m_texture);
}

float Entity::GetX() const
{
	return m_x;
}

float Entity::GetY() const
{
	return m_y;
}

int Entity::GetWidth() const
{
	return m_width;
}

int Entity::GetHeight() const 
{
	return m_height;
}

void Entity::SetAlive(bool alive)
{
	m_alive = alive;
}

bool Entity::GetAlive() const
{
	return m_alive;
}

int* Entity::GetHealthPtr()
{
	return &m_health;
}

int Entity::GetHealth() const
{
	return m_health;
}

void Entity::IncreaseHealth(int health)
{
	m_health += health;
}

void Entity::SetDelete(bool d)
{
	m_delete = d;
}

bool Entity::GetDelete() const
{
	return m_delete;
}