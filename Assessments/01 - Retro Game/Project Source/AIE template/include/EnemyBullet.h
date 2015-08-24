/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and update function unique to the enemyBullet class				
**/

#pragma once

#include "Entity.h"

class EnemyBullet : public Entity
{
private:

protected:

public:
	//enemy bullet contructor
	//xPos is the x coordinate to spawn at
	//yPos is the y coordinate to spawn at
	EnemyBullet(const float xPos,const float yPos);

	//moves enemy bullets down the screen
	void Update(float deltaTime);
};