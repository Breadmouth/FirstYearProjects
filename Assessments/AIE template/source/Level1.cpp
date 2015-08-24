#include "Level1.h"
#include "AIE.h"
#include <cstdlib>
#include <time.h>

Level1::Level1() 
{
	Initialise( 640, 780, false, "Template");

	srand(time(NULL));

	player = new Player;
	background = new Background;

	
	m_shotCooldown = 0.0f;
	m_shotResetTime = 0.50f;

	m_enemySpawnCooldown = 0.0f;
	m_enemySpawnResetTime = 1.30f;
}

void Level1::Update()
{
	m_deltaTime = GetDeltaTime();

	//decreases the cooldowns based on delta time
 	m_shotCooldown -= m_deltaTime;
	m_enemyShotCooldown -= m_deltaTime;
	m_enemySpawnCooldown -= m_deltaTime;

	//spawns an enemy if the cooldown is ready
	if (m_enemySpawnCooldown < 0.0f)
	{
		AddEnemy();
		m_enemySpawnCooldown = m_enemySpawnResetTime;
	}

	//adds a bullet if both the space key is being held and the shot cooldown is ready
	if (player->Update(m_deltaTime) &&  m_shotCooldown < 0.0f)
	{
		AddBullet(player->GetX(), player->GetY());
		m_shotCooldown = m_shotResetTime;
	}

	//checks collision between bullets and enemies and deletes any bullets and enemies that collide
	for (int i = 0; i < m_bullets.size(); i++)
	{
		for (int x = 0; x < m_enemies.size(); x++)
		{
			if ((m_bullets[i]->GetX() + 2 < (m_enemies[x]->GetX() + m_enemies[x]->GetWidth()) && m_bullets[i]->GetX() + 2 > m_enemies[x]->GetX()) && (m_bullets[i]->GetY() > (m_enemies[x]->GetY() - m_enemies[x]->GetHeight()) && m_bullets[i]->GetY() < m_enemies[x]->GetY()))
			{
				m_enemies[x]->SetAlive(false);
				m_bullets[i]->SetAlive(false);
			}
		}
	}

	//updates bullets and checks if they are out of the screen bounds
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->GetY() > 780 && m_bullets[i]->GetY() < 0)
			m_bullets[i]->SetAlive(false);

		m_bullets[i]->Update(m_deltaTime);
	}

	//updates enemies, adds enemy bullets, and checks if enemies are out of the screen bounds
	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->GetY() < 0)
			m_enemies[i]->SetAlive(false);

		m_enemies[i]->Update(m_deltaTime);
		if (m_enemies[i]->Fire() == true)
		{
			AddEnemyBullet(m_enemies[i]->GetX() + (m_enemies[i]->GetWidth()/2), m_enemies[i]->GetY());
		}

	}

	//updates enemyBullets and checks if they are out of the screen bounds
	for (int i = 0; i < m_enemyBullets.size(); i++)
	{
		if (m_enemyBullets[i]->GetY() < 0)
			m_enemyBullets[i]->SetAlive(false);

		m_enemyBullets[i]->Update(m_deltaTime);
	}
	
	//deletes anemyBullets that are not alive
	auto j = m_enemyBullets.begin();
	while ( j != m_enemyBullets.end())
	{
		if ((*j)->GetAlive() == false)
		{
			delete (*j);
			j = m_enemyBullets.erase(j);
		}
		else
			j++;
	}

	//deletes bullets that are not alive
	auto i = m_bullets.begin();
	while ( i != m_bullets.end())
	{
		if ((*i)->GetAlive() == false)
		{
			delete (*i);
			i = m_bullets.erase(i);
		}
		else
			i++;
	}

	//deletes enemies that are not alive
	auto x = m_enemies.begin();
	while ( x != m_enemies.end())
	{
		if ((*x)->GetAlive() == false)
		{
			delete (*x);
			x = m_enemies.erase(x);
		}
		else
			x++;
	}

}

void Level1::Draw()
{
	SetBackgroundColour (SColour( 7, 9, 27, 156));
	ClearScreen();
	background->Scroll(m_deltaTime);

	for (int i = 0; i < m_bullets.size(); i++)
		m_bullets[i]->Draw();

	for (int i = 0; i < m_enemyBullets.size(); i++)
	{
		m_enemyBullets[i]->Draw();
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Draw();
	}

	player->Draw();

	
	
}

void Level1::AddBullet(float xPos, float yPos)
{
  	Bullet* newBullet = new Bullet(xPos +62, yPos);
	m_bullets.push_back(newBullet);
}

void Level1::AddEnemy()
{
	Enemy* newEnemy = new Enemy();
	m_enemies.push_back(newEnemy);
}

void Level1::AddEnemyBullet(float xPos, float yPos)
{
	EnemyBullet* newBullet = new EnemyBullet(xPos, yPos);
	m_enemyBullets.push_back(newBullet);
}

Level1::~Level1()
{
	delete player;
	delete background;
}

