/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the Level2 class				
**/

#pragma once

#include "Level.h"

class Level2 : public Level
{

public:

	Level2(unsigned int width, unsigned int height, ScreenManager* sm);

	~Level2();

	//creates a new enemy at a random position at the top of the screen
	//velocity is the speed for the enemy to move at
	void AddEnemy(const float velocity);
};