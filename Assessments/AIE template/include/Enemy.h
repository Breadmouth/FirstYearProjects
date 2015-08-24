#pragma once

#include "Entity.h"
#include "EnemyBullet.h"
#include <vector>

class Enemy : public Entity
{
private:
	float m_shotCooldown;
	float m_shotResetTime;
protected:

public:
	Enemy();

	void Update(float dt);

	bool Fire();

	~Enemy();

};