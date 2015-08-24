/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the Level1 class		
*			This header is required for all classes that inherit from it:
*			PlayerSpeedy
**/

#pragma once

#include "Player.h"

class PlayerSpeedy : public Player
{
	public:
		PlayerSpeedy();

		//updates the player object based on user input with increased movement speed
		bool Update(float deltaTime);
};