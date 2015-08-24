#pragma once
#include "sprite.h"

class Game;

class Particle :	public Sprite
{
public:
	Particle();
	Particle(Game* game, const char* textureName, int width, int height);
	void Update(float deltaTime);

	void SetAlive(bool alive);
	bool GetAlive()	const;

private:
	float m_deathTime;
	bool m_alive;
};

