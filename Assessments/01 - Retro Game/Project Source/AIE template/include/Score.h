/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the Score class				
**/

#pragma once

#include <sstream>
#include <iostream>

class Score
{
private:
	int m_score;

	int m_scoreBar;
	int m_healthSprite;

public:
	Score();

	//draw the score and health to the screen
	void Draw(int* health);

	//increases the score
	//score is the ammount to increase the Score by
	void Update(int score);

	int GetScore();

	void Reset();


};