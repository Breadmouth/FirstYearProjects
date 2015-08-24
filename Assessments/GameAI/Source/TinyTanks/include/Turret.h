#pragma once
#include "Sprite.h"
#include "Tank.h"
#include "BulletManager.h"

class Game;

class Turret : public Sprite
{
public:
	Turret();
	Turret(Game* game, BulletManager* bulletManager, const char* textureName, int width, int height, int left, int right, int shoot);
	Turret(Game* game, BulletManager* bulletManager, const char* textureName, int width, int height);

	void Update(float deltaTime);

private:
	BulletManager* m_bulletManager;
	int m_keyLeft;
	int m_keyRight;
	int m_keyShoot;

	float m_bulletCountdown;
	bool m_ai;
};
