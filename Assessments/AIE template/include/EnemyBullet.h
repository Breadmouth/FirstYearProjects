#pragma once

#include "Entity.h"

class EnemyBullet : public Entity
{
private:

protected:

public:
	EnemyBullet(float xPos, float yPos);

	void Update(float dt);
};