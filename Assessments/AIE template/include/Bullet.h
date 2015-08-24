#pragma once

#include "Entity.h"

class Bullet : public Entity
{
private:

protected:

public:
	Bullet(float xPos, float yPos);

	void Update(float dt);
};