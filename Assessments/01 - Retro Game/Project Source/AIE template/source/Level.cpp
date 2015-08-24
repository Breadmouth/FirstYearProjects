#include "Level.h"
#include "AIE.h"
#include "ScreenManager.h"
#include "sqlite3.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

Level::Level(unsigned int width, unsigned int height, ScreenManager* sm) 
	:Screen(width, height, sm)
{
	srand(time(NULL));

	player = new PlayerSpeedy();
	score = new Score();

	m_background1Y = 3200.0f;
	m_background2Y = 6399.0f;

	m_enemySpawnCooldown = 0.0f;
	m_enemySpawnResetTime = 1.30f;

	m_levelLength = 40.0f;
	m_levelCurrentTime = 0.0f;

	console = GetConsoleWindow(); 
	game = GetForegroundWindow();

}

void Level::Update(float deltaTime)
{

	//increase the m_levelCurrentTime to keep track of how long the level has been played/how long until the level ends
	m_levelCurrentTime += deltaTime;

	//end the level if the time reaches its end
	if (m_levelCurrentTime >= m_levelLength)
	{
		SetForegroundWindow(console);
		std::cout << "Please type your name: ";
		std::cin >> m_playerName;
		SetForegroundWindow(game);
		SaveScore();
		m_sm->ResetScreen();
		m_sm->SetScreen(7);
	}

	//decreases the cooldowns based on delta time
	m_enemySpawnCooldown -= deltaTime;

	//spawns an enemy if the cooldown is ready
	if (m_enemySpawnCooldown < 0.0f)
	{
		AddEnemy(180);
		m_enemySpawnCooldown = m_enemySpawnResetTime;
	}

	//adds a bullet if both the space key is being held and the shot cooldown is ready
	if (player->Update(deltaTime))
	{
		AddBullet(player->GetX(), player->GetY());
	}

	if (IsKeyDown(KEY_ESCAPE))
	{
		m_sm->SetScreen(6);
	}

	//checks collision between bullets and enemies and deletes any bullets and enemies that collide
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		for (unsigned int x = 0; x < m_enemies.size(); x++)
		{
			if ((m_bullets[i]->GetX() + 2 < (m_enemies[x]->GetX() + m_enemies[x]->GetWidth()) && m_bullets[i]->GetX() + 2 > m_enemies[x]->GetX())&& (m_bullets[i]->GetY() > (m_enemies[x]->GetY() - m_enemies[x]->GetHeight()) && m_bullets[i]->GetY() < m_enemies[x]->GetY()) && m_enemies[x]->GetAlive())
			{
				m_enemies[x]->IncreaseHealth(-1);
				if (m_enemies[x]->GetHealth() == 0)
				{
					score->Update(m_enemies[x]->GetScore());
					m_enemies[x]->Die(deltaTime);
					m_enemies[x]->SetAlive(false);
				}
				m_bullets[i]->SetDelete(true);
			}
		}
	}

	//checks collision between enemy bullets and the player
	for (unsigned int i = 0; i < m_enemyBullets.size(); i++)
	{

		if ((m_enemyBullets[i]->GetX() + 2 < (player->GetX() + player->GetWidth()) && m_enemyBullets[i]->GetX() + 2 > player->GetX()) && (m_enemyBullets[i]->GetY() > (player->GetY() - player->GetHeight()) && (m_enemyBullets[i]->GetY()- m_enemyBullets[i]->GetHeight()) < player->GetY()))
		{
			player->IncreaseHealth(-1);
			if (player->GetHealth() <= 0)
				player->SetAlive(false);
			m_enemyBullets[i]->SetDelete(true);
		}

	}

	//checks collision between enemies and player
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{

		if ((m_enemies[i]->GetX() < (player->GetX() + player->GetWidth()) && (m_enemies[i]->GetX() + m_enemies[i]->GetWidth()) > player->GetX()) && (m_enemies[i]->GetY() > (player->GetY() - player->GetHeight()) && (m_enemies[i]->GetY()- m_enemies[i]->GetHeight()) < player->GetY()) && m_enemies[i]->GetAlive())
		{
			player->IncreaseHealth(-1);
			if (player->GetHealth() <= 0)
				player->SetAlive(false);
			score->Update(m_enemies[i]->GetScore());
			m_enemies[i]->Die(deltaTime);
			m_enemies[i]->SetAlive(false);
			
		}

	}

	//updates bullets and checks if they are out of the screen bounds
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->GetY() > 780 && m_bullets[i]->GetY() < 40)
			m_bullets[i]->SetDelete(true);

		m_bullets[i]->Update(deltaTime);
	}

	//updates enemies, adds enemy bullets, and checks if enemies are out of the screen bounds
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->GetY() < 40)
			m_enemies[i]->SetDelete(true);

		m_enemies[i]->Update(deltaTime);
		if (m_enemies[i]->Fire() == true)
		{
			AddEnemyBullet(m_enemies[i]->GetX() + (m_enemies[i]->GetWidth()/2), m_enemies[i]->GetY());
		}

	}

	//updates enemyBullets and checks if they are out of the screen bounds
	for (unsigned int i = 0; i < m_enemyBullets.size(); i++)
	{
		if (m_enemyBullets[i]->GetY() < 40)
			m_enemyBullets[i]->SetDelete(true);

		m_enemyBullets[i]->Update(deltaTime);
	}
	
	//deletes enemyBullets that are marked for delete
	auto j = m_enemyBullets.begin();
	while ( j != m_enemyBullets.end())
	{
		if ((*j)->GetDelete() == true)
		{
			delete (*j);
			j = m_enemyBullets.erase(j);
		}
		else
			j++;
	}

	//deletes bullets that are marked for delete
	auto i = m_bullets.begin();
	while ( i != m_bullets.end())
	{
		if ((*i)->GetDelete() == true)
		{
			delete (*i);
			i = m_bullets.erase(i);
		}
		else
			i++;
	}

	//deletes enemies that are marked for delete
	auto x = m_enemies.begin();
	while ( x != m_enemies.end())
	{
		if ((*x)->GetDelete() == true)
		{
			delete (*x);
			x = m_enemies.erase(x);
		}
		else
			x++;
	}

	//checks if the player is dead and ends the game if he is
	if (player->GetAlive() ==  false)
	{
		SetForegroundWindow(console);
		std::cout << "Please type your name: ";
		std::cin >> m_playerName;
		SetForegroundWindow(game);
		SaveScore();
		m_sm->ResetScreen();
		m_sm->SetScreen(7);
	}
}

void Level::Draw(float deltaTime)
{
	SetBackgroundColour (SColour( 7, 9, 27, 156));
	ClearScreen();
	Scroll(deltaTime);

	for (unsigned int i = 0; i < m_bullets.size(); i++)
		m_bullets[i]->Draw();

	for (unsigned int i = 0; i < m_enemyBullets.size(); i++)
	{
		m_enemyBullets[i]->Draw();
	}

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->GetAlive())
			m_enemies[i]->Draw();
		else
			m_enemies[i]->Die(deltaTime);
	}

	player->Draw();

	player->DrawPropulsion(deltaTime);

	score->Draw(player->GetHealthPtr());
	
	
}

void Level::AddBullet(float xPos, float yPos)
{
  	Bullet* newBullet = new Bullet(xPos +62, yPos);
	m_bullets.push_back(newBullet);
}

void Level::AddEnemyBullet(float xPos, float yPos)
{
	EnemyBullet* newBullet = new EnemyBullet(xPos, yPos);
	m_enemyBullets.push_back(newBullet);
}

Level::~Level()
{
	delete player;
	delete score;

}

void Level::Scroll(float deltaTime)
{

	m_background1Y -= (150 * deltaTime);

	MoveSprite(m_background, 0, m_background1Y);
	DrawSprite(m_background);

	m_background2Y -= (150 * deltaTime);

	MoveSprite(m_background, 0, m_background2Y);
	DrawSprite(m_background);

	if (m_background1Y <= 0)
	{
		m_background1Y = 3200.0f;
		m_background2Y = 6399.0f;
	}
}

void Level::SaveScore()
{
	sqlite3 *dataBase = NULL;
	sqlite3_open ( "game_db", &dataBase);

	if ( dataBase == NULL )
		return;

	std::string create_table_query =
	"CREATE TABLE IF NOT EXISTS \"tbl_scores\" "\
	"("											\
		"\"id\" INT PRIMARY KEY,"				\
		"\"name\" varchar(32) NOT NULL,"		\
		"\"score\" INT NOT NULL"				\
	");";										

	char *err = NULL;
	sqlite3_exec( dataBase, create_table_query.c_str(), NULL, NULL, &err);

	if ( err != NULL)
	{
		std::cout << err << std::endl;
		system("pause");
		sqlite3_close( dataBase );
		return;
	}

	//insert score into tbl_scores

	std::string insert_query_tmp =
	"INSERT INTO \"tbl_scores\" (\"name\", \"score\")" \
	"VALUES ( \"%s\", %i);" ;

	char buffer[256];
	sprintf ( buffer, insert_query_tmp.c_str(), m_playerName.c_str(), score->GetScore() );

	sqlite3_exec( dataBase, buffer, NULL, NULL, &err);


	sqlite3_close (dataBase);
}

void Level::Reset()
{
	
	auto j = m_enemyBullets.begin();
	while ( j != m_enemyBullets.end())
	{
		delete (*j);
		j = m_enemyBullets.erase(j);
	}
	

	auto i = m_bullets.begin();
	while ( i != m_bullets.end())
	{
		delete (*i);
		i = m_bullets.erase(i);
	}

	auto x = m_enemies.begin();
	while ( x != m_enemies.end())
	{
		delete (*x);
		x = m_enemies.erase(x);
	}

	player->Reset();
	score->Reset();

	m_background1Y = 3200.0f;
	m_background2Y = 6399.0f;

	m_enemySpawnCooldown = 0.0f;

	m_levelCurrentTime = 0.0f;
}