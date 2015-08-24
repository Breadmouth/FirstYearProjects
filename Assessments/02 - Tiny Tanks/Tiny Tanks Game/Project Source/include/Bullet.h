#pragma once
#include "sprite.h"

class Game;

class Bullet :	public Sprite
{
public:
	Bullet();
	Bullet(Game* game, const char* textureName, int width, int height);
	void Update(float deltaTime);
	void FixPosition();

	void SetAlive(bool alive);
	bool GetAlive()	const;

private:
	bool m_alive;
};

