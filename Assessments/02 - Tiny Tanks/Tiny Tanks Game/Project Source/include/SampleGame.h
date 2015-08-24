#pragma once

#include <vector>
#include "Game.h"
#include "BulletManager.h"
#include "Time.h"

class GameState;

class SampleGame: public Game
{
protected:
	GameState* m_playingState;
	GameState* m_splashScreen;

public:
	SampleGame();
	~SampleGame();

	virtual void Update(float deltaTime);
	virtual void Draw(float deltaTime);
	virtual void Init();
	virtual void Deinit();
};