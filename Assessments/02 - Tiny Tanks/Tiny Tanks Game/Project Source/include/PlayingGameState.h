#pragma once

#include "GameState.h"
#include <vector>

class Sprite;
class BulletManager;
class ParticleManager;
class Game;

class PlayingGameState: public GameState
{
protected:
	Sprite* m_tank;
	Sprite* m_turret;
	Sprite* m_tank2;
	Sprite* m_turret2;
	Sprite* m_background;
	BulletManager* m_bulletManager;
	ParticleManager* m_particleManager;

	Game* m_game;
public:
	PlayingGameState(Game* game);
	~PlayingGameState();

	virtual void Update(float deltaTime);
	virtual void Draw(float deltaTime);
	virtual void Init();
	virtual void Init(unsigned int width, unsigned int height, const char* title);
	virtual void Deinit();
};