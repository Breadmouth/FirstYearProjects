/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the Pause class				
**/

#pragma once

#include "Screen.h"

class Pause : public Screen
{
private:

	int m_btn1;
	int m_btn2;

	enum Selection {PLAY, QUIT, SAVE, LOAD};
	Selection currentSelection;


public:

	Pause(unsigned int width, unsigned int height, ScreenManager* sm);

	~Pause();

	//updates the pause screen based on user input
	void Update(float deltaTime);
	
	//draws the buttons to screen
	void Draw(float deltaTime);	

	void Reset();


};