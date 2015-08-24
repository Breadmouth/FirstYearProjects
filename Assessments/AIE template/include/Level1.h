#pragma once

#include "player.h"
#include "Background.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"

class Level1
{

private:

	Background* background;
	Player* player;

	float m_deltaTime;

	
	std::vector<Bullet*> m_bullets;
	std::vector<Enemy*> m_enemies;
	std::vector<EnemyBullet*> m_enemyBullets;

	float m_shotCooldown;
	float m_shotResetTime;

	float m_enemyShotCooldown;
	float m_enemyShotResetTime;

	float m_enemySpawnCooldown;
	float m_enemySpawnResetTime;

public:
	Level1();
	~Level1();

	void Update();

	void Draw();

	void AddBullet(float xPos, float yPos);

	void AddEnemy();

	void AddEnemyBullet(float xPos, float yPos);

};