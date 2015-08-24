#include "Turret.h"
#include "Game.h"

Turret::Turret(Game* game, BulletManager* bulletManager, const char* textureName, int width, int height, int left, int right, int shoot)
	: Sprite(game, textureName, width, height)
{
	m_game = game;
	Init();
	LoadTexture(textureName);
	m_width = width; 
	m_height = height;
	m_bulletManager = bulletManager;
	m_anchor = Vector2(0.5, 0.25);
	m_keyLeft = left;
	m_keyRight = right;
	m_keyShoot = shoot;

	m_bulletCountdown = 0.00f;

	m_ai = false;
}

Turret::Turret(Game* game, BulletManager* bulletManager, const char* textureName, int width, int height)
	: Sprite(game, textureName, width, height)
{
	m_game = game;
	Init();
	LoadTexture(textureName);
	m_width = width; 
	m_height = height;
	m_bulletManager = bulletManager;
	m_anchor = Vector2(0.5, 0.25);

	m_bulletCountdown = 0.00f;

	m_ai = true;
}

void Turret::Update(float deltaTime)
{
	if ( !m_ai )
	{
		if (glfwGetKey(m_game->GetWindow(), m_keyLeft))
		{
			m_rotation -= 0.4f * deltaTime;
		}
		if (glfwGetKey(m_game->GetWindow(), m_keyRight))
		{
			m_rotation += 0.4f * deltaTime;
		}

		if (glfwGetKey(m_game->GetWindow(), m_keyShoot) && m_bulletCountdown <= 0)
		{
			m_bulletManager->AddBullet(m_worldTransform.GetTranslation(), 3.1415926535f + m_worldTransform.GetRotation());
			m_bulletCountdown = 0.50f;
		}
	}

	Sprite::Update(deltaTime);
	m_bulletCountdown -= deltaTime;
}