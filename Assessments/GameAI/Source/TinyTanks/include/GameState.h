#pragma once

class GameStateManager;

class GameState
{
protected:
	GameStateManager * m_gsm;

public:
	GameState(GameStateManager* gsm);
	virtual ~GameState();
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(float deltaTime) = 0;
	virtual void Init() = 0;
	virtual void Deinit() = 0;
};