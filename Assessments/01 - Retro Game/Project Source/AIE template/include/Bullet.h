/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and update function unique to the bullet class				
**/

#pragma once

#include "Entity.h"

class Bullet : public Entity
{
private:

protected:

public:
	//bullet constructor
	//xPos is the x coordinate to spawn at
	//yPos is the y coordinate to spawn at
	Bullet(float xPos, float yPos);

	//moves the bullet upwards
	void Update(float deltaTime);
};