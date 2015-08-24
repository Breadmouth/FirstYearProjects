#include "PlayingGameState.h"
#include "Tank.h"
#include "Turret.h"
#include "Vec2.h"
#include "Game.h"
#include "ParticleManager.h"
#include <GLFW/glfw3.h>

PlayingGameState::PlayingGameState(Game* game) : GameState(game->GetGameStateManager()), m_game(game)
{

}

PlayingGameState::~PlayingGameState()
{

}
void PlayingGameState::Init()
{
	Init(800, 600, "Test");
}



void PlayingGameState::Init(unsigned int width, unsigned int height, const char* title)
{
	
	m_bulletManager = new BulletManager(m_game);
	m_particleManager = new ParticleManager(m_game);

	//pointer to this, width, height, up, down, left right
	m_tank = new Tank(m_game, "Tank2.png", 50, 100, Vector2(100, 300), 'W', 'S', 'A', 'D');
	m_tank2 = new Tank(m_game, "Tank.png", 50, 100, Vector2(700, 300), GLFW_KEY_KP_8, GLFW_KEY_KP_5, GLFW_KEY_KP_4, GLFW_KEY_KP_6);
	m_turret = new Turret(m_game, m_bulletManager, "Turret.png", 40, 80, 'Q', 'E', GLFW_KEY_SPACE);
	m_turret2 = new Turret(m_game, m_bulletManager, "Turret.png", 40, 80, GLFW_KEY_KP_7, GLFW_KEY_KP_9, GLFW_KEY_KP_ENTER);
	m_background = new Sprite(m_game, "Background.png", 800, 600);

	m_tank->AddChild(m_turret);
	m_tank2->AddChild(m_turret2);
}

void PlayingGameState::Deinit()
{
	delete m_tank;
	delete m_tank2;
	delete m_turret;
	delete m_turret2;
	delete m_bulletManager;
	delete m_particleManager;
	delete m_background;
}

void PlayingGameState::Draw(float deltaTime)
{
	m_background->Draw(deltaTime);
	m_tank->Draw(deltaTime);
	m_tank2->Draw(deltaTime);
	m_turret->Draw(deltaTime);
	m_turret2->Draw(deltaTime);
	m_bulletManager->Draw(deltaTime);
	m_particleManager->Draw(deltaTime);
}

void PlayingGameState::Update(float deltaTime)
{
	m_tank->Update(deltaTime);
	m_tank2->Update(deltaTime);
	m_bulletManager->Update(deltaTime);

	//rectangular bounding collision between tanks and bullets && bullets and walls

	std::vector<Bullet*>* m_bullets = m_bulletManager->GetBullets();
	Vector3 temp_bullet;

	for ( auto i = m_bullets->begin(); i != m_bullets->end(); i++)
	{
		Vector2 pos = (*i)->GetPosition();
		temp_bullet = m_tank->Invert() * pos;

		if (temp_bullet.x < (m_tank->GetWidth() / 2) && temp_bullet.x > (- m_tank->GetWidth() / 2) && temp_bullet.y < (+ m_tank->GetHeight() / 2) && temp_bullet.y > (- m_tank->GetHeight() / 2))
		{
			(*i)->SetAlive(false);

			for (int j = 0; j < 10; ++j)
			{
				m_particleManager->AddParticle((*i)->GetPosition());
			}
		}

		temp_bullet = m_tank2->Invert() * pos;

		if (temp_bullet.x < (m_tank2->GetWidth() / 2) && temp_bullet.x > (- m_tank2->GetWidth() / 2) && temp_bullet.y < (+ m_tank2->GetHeight() / 2) && temp_bullet.y > (- m_tank2->GetHeight() / 2))
		{
			(*i)->SetAlive(false);

			for (int j = 0; j < 10; ++j)
			{
				m_particleManager->AddParticle((*i)->GetPosition());
			}
		}

		if ((*i)->GetPosition().x > 800 || (*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 600 || (*i)->GetPosition().y < 0)
		{
			(*i)->SetAlive(false);
		}
	}

	// circular bounding collision check between tanks
	if (Vector2 (m_tank->GetPosition().x - m_tank2->GetPosition().x, m_tank->GetPosition().y - m_tank2->GetPosition().y).GetLength() < m_tank->GetRadius() + m_tank2->GetRadius())
	{
		m_tank->SetPosition(m_tank->GetPreviousPosition());
		m_tank2->SetPosition(m_tank2->GetPreviousPosition());
	}

	//circular collisions between tanks and walls
	if (m_tank->GetPosition().x + m_tank->GetRadius() > m_game->GetScreenWidth() || m_tank->GetPosition().x - m_tank->GetRadius() < 0 || m_tank->GetPosition().y + m_tank->GetRadius() > m_game->GetScreenHeight() || m_tank->GetPosition().y - m_tank->GetRadius() < 0)
		m_tank->SetPosition(m_tank->GetPreviousPosition());

	if (m_tank2->GetPosition().x + m_tank2->GetRadius() > m_game->GetScreenWidth() || m_tank2->GetPosition().x - m_tank2->GetRadius() < 0 || m_tank2->GetPosition().y + m_tank2->GetRadius() > m_game->GetScreenHeight() || m_tank2->GetPosition().y - m_tank2->GetRadius() < 0)
		m_tank2->SetPosition(m_tank2->GetPreviousPosition());
		
	//delete bullets that are dead
	for ( auto i = m_bullets->begin(); i != m_bullets->end(); i++)
	{
		if ((*i)->GetAlive() == false)
		{
			m_bullets->erase(i);
			return;
		}
	}

	m_particleManager->Update(deltaTime);
}