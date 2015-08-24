/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the enemy class				
**/

#pragma once

#include "Entity.h"
#include "EnemyBullet.h"
#include <vector>

class Enemy : public Entity
{
protected:
	//time to next shot
	float m_shotCooldown;

	//reset time between shots
	float m_shotResetTime;

	//speed the enemy is moving at
	float m_velocity;

	//sprite 1 for explosion animation
	int m_deathTexture1;

	//sprite 2 for explosion animation
	int m_deathTexture2;

	//sprite 3 for explosion animation
	int m_deathTexture3;

	//counter that designates what time to draw which sprites for the death animation
	float m_deathTime;

	int m_score;

public:
	//constructor for enemy
	//velocity is the speed for the enemy to move
	Enemy(const float veloctiy);

	//moves the enemy down the screen
	void Update(float deltaTime);
	
	//call to make the enemy shoot, as long as their cooldown is ready
	bool Fire();

	//handles the enemies death animation
	void Die(float deltaTime);

	int GetScore();

	//enemy deconstructor
	~Enemy();

};