/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the LevelSelect class				
**/

#pragma once

#include "Screen.h"

class LevelSelect : public Screen
{
private:
	enum Selection {LEVEL1, LEVEL2, LEVEL3};
	Selection currentSelection;

	float m_space1Y;
	float m_space2Y;

	int m_space;
	int m_title;
	int m_level1;
	int m_level2;
	int m_level3;
	int m_pointer;

public:
	LevelSelect(unsigned int width, unsigned int height, ScreenManager* sm);

	~LevelSelect();

	//updates the level select screen based on user input
	void Update(float deltaTime);

	//draws background, buttons and title to screen
	void Draw(float deltaTime);

	void Reset();

};