#include "BulletManager.h"
#include "Game.h"

BulletManager::BulletManager(Game* game)
{
	m_game = game;
}

BulletManager::~BulletManager()
{
	for ( auto i = m_bullets.begin(); i != m_bullets.end(); )
	{
		(i) = m_bullets.erase(i);
		delete (*i);
	}
	delete m_bullet;
}

void BulletManager::AddBullet(Vector2 position, float a_rotation)
{
	m_bullet = new Bullet( m_game, "Bullet.png", 5, 10);
	m_bullet->SetPosition( position.x, position.y);
	m_bullet->SetRotation(a_rotation);
	m_bullet->FixPosition();
	m_bullets.push_back(m_bullet);
}

void BulletManager::Update(float deltaTime)
{

	for ( auto i = m_bullets.begin(); i != m_bullets.end(); i++)
	{
		(*i)->Update(deltaTime);
	}

	for ( auto i = m_bullets.begin(); i != m_bullets.end(); i++)
	{
		if ((*i)->GetAlive() == false)
		{
			m_bullets.erase(i);
			return;
		}
	}

}

void BulletManager::Draw(float deltaTime)
{
	for ( auto i = m_bullets.begin(); i != m_bullets.end(); i++)
	{
		(*i)->Draw(deltaTime);
	}
}

std::vector<Bullet*>* BulletManager::GetBullets()
{
	return &m_bullets;
}
