/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the Player class				
**/

#pragma once

#include "Entity.h"
#include <iostream>
#include <vector>

class Player : public Entity
{
	protected:

		int m_propulsion1;
		int m_propulsion2;
		int m_propulsion3;

		float m_propulsionReset;

		float m_shotCooldown;
		float m_shotResetTime;

	public:
		Player();

		//updates the player object based on user input
		virtual bool Update(float deltaTime) = 0;

		//draws the propulsion sprites behind the player sprite
		void DrawPropulsion(float deltaTime);

		void Reset();
};