/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the Menu class				
**/

#pragma once

#include "Screen.h"

class Menu : public Screen
{
private:

	int m_space;
	int m_title;
	int m_btn1;
	int m_btn2;

	enum Selection {PLAY, QUIT, SCORES};
	Selection currentSelection;

	float m_space1Y;
	float m_space2Y;


public:
Menu(unsigned int width, unsigned int height, ScreenManager* sm);

~Menu();

//updates the menu screen based on user input
void Update(float deltaTime);

//draws the background, buttons and title to screen
void Draw(float deltaTime);

void Reset();
};