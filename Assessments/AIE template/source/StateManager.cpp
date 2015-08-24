#include "StateManager.h"

StateManager::StateManager()
{
	GameState state = SPLASH;
}

StateManager::GameState StateManager::RunLevel1()
{
	return LEVEL1;
}