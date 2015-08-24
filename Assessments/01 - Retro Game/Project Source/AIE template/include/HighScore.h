/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the LevelEnd class				
**/

#pragma once

#include "Screen.h"
#include <vector>
#include <string>

struct HighScoreEntry
{
	std::string name;
	unsigned int score;
};

class HighScore : public Screen
{
private:
	int m_space;
	int m_title;

	float m_space1Y;
	float m_space2Y;

	std::vector<HighScoreEntry> m_highScores;

public:

	HighScore(unsigned int width, unsigned int height, ScreenManager* sm);

	~HighScore();

	static int sqlite_query_callback( void *userdata, int numArgs, char **data, char **columnName);

	//updates the pause screen based on user input
	void Update(float deltaTime);
	
	//draws the buttons to screen
	void Draw(float deltaTime);	

	//loads scores from game_db to game
	void LoadScores();

	void Reset();


};