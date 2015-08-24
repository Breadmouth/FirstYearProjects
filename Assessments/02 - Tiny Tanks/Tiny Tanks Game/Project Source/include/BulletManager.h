#pragma once
#include <vector>
#include "Bullet.h"
#include "Vec2.h"

class Game;

class BulletManager
{
public:
	BulletManager(Game* game);
	~BulletManager();

	void AddBullet(Vector2 position, float a_rotation);
	void Update(float deltaTime);
	void Draw(float deltaTime);

	std::vector<Bullet*>* GetBullets();

protected:
	Bullet* m_bullet;
	std::vector<Bullet*> m_bullets;

	Game* m_game;
};