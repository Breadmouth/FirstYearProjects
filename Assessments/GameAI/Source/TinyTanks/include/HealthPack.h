#pragma once
#include "Sprite.h"

class HealthPack : public Sprite
{
public:
	HealthPack(Game* game, const char* textureName, int width, int height, Vector2 pos);
	void Update(float deltaTime);
};