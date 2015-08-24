#pragma once

#include "Entity.h"
#include <iostream>
#include <vector>

class Player : public Entity
{
	private:

	public:
		Player();

		bool Update(float dt);
};