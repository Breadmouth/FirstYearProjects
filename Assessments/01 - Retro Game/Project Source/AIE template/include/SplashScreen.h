/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the SplashScreen class	
**/

#pragma once

#include "Screen.h"

class SplashScreen : public Screen
{
private:
	int m_splash;

	float m_splashCooldown;

public:
	SplashScreen(unsigned int width, unsigned int height, ScreenManager* sm);

	//updates the splashscreen
	void Update(float deltaTime);

	//draws the splash screen
	void Draw(float deltaTime);
	void Reset();
};