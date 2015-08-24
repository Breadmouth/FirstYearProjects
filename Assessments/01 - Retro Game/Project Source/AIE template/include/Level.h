/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the Level class	
*			this header is required for all classes that inherit from it:
*			Level1, Level2, Level3
**/

#pragma once

#include "PlayerSpeedy.h"
#include "Score.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyAdvanced.h"
#include "EnemyBullet.h"
#include "Screen.h"

#include <Windows.h>
#include <string>

class Level : public Screen
{

protected:

	Score* score;
	Player* player;
	
	std::vector<Bullet*> m_bullets;
	std::vector<Enemy*> m_enemies;
	std::vector<EnemyBullet*> m_enemyBullets;

	int m_background;

	std::string m_playerName;

	float m_background1Y;
	float m_background2Y;

	float m_enemySpawnCooldown;
	float m_enemySpawnResetTime;

	float m_levelLength;
	float m_levelCurrentTime;

	HWND console; 
	HWND game;

public:
	Level(unsigned int width, unsigned int height, ScreenManager* sm);

	~Level();

	//makes all neccessary checks and calculations, and calls update on all objects on screen
	void Update(float deltaTime);
	
	//draws objects on screen
	void Draw(float deltaTime);

	//creates a new bullet
	//xPos is x coordinate to spawn at
	//yPos is the y coordinate to spawn at
	void AddBullet(const float xPos,const float yPos);

	//creates a new enemy at a random position at the top of the screen
	//velocity is the speed for the enemy to move at
	virtual void AddEnemy(const float velocity) = 0;

	//creates a new EnemyBullet
	//xPos is x coordinate to spawn at
	//yPos is the y coordinate to spawn at
	virtual void AddEnemyBullet(float xPos, float yPos);

	//moves and draws the background
	void Scroll(float deltaTime);

	void SaveScore();

	//resets all changable variables to default values
	void Reset();

};