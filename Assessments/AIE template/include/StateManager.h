#pragma once

#include "Level1.h"

class StateManager
{
private:
	enum GameState {LEVELSELECT, SHIPSELECT, LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, MENU, PAUSE, SCORES, QUIT, SPLASH};

	Level1* m_game;

protected:

public:
	StateManager();

	GameState RunLevel1();
	GameState RunMenu();
	GameState RunLevelSelect();
	GameState RunShipSelect();
	GameState RunPause();
	GameState RunScores();
	GameState RunQuit();
	GameState RunSplash();
};