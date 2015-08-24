/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the Screen class	
*			this header is required for all classes that inherit from it:
*			Level, Menu, Pause, SplashScreen, LevelSelect
**/

#pragma once

class ScreenManager;

class Screen
{
protected:
	unsigned int m_width;
	unsigned int m_height;

	ScreenManager* m_sm;

public:
	Screen (unsigned int width, unsigned int height, ScreenManager* sm);

	virtual ~Screen();

	virtual void Update(float deltaTime) = 0;

	virtual void Draw(float deltaTime) = 0;

	virtual void Reset() = 0;

};
