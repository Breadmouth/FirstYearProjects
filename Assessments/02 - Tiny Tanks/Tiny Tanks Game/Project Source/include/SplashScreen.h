#pragma once

#include "GameState.h"

class Game;
class Sprite;

class SplashScreen : public GameState
{
protected:
	Game* m_game;
	Sprite* m_bg;
	float m_countDown;
public:
	SplashScreen(Game* game);
	virtual ~SplashScreen();

	virtual void Update(float deltaTime);
	virtual void Draw(float deltaTime);
	virtual void Init();
	virtual void Deinit();

};