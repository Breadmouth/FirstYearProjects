/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the enemy class				
**/

#pragma once

#include "Enemy.h"
#include "EnemyBullet.h"
#include <vector>

class EnemyAdvanced : public Enemy
{
private:

protected:

public:
	//constructor for enemy
	//velocity is the speed for the enemy to move
	EnemyAdvanced(const float veloctiy);

	//enemy deconstructor
	~EnemyAdvanced();

};