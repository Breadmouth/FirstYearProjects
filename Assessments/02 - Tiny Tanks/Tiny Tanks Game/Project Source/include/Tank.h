#pragma once
#include "Sprite.h"

class Game;

class Tank : public Sprite
{
public:
	Tank();
	Tank(Game* game, const char* textureName, int width, int height, 
		Vector2 pos, int up, int down, int left, int right);

	void Update(float deltaTime);
private:
	int m_keyLeft;
	int m_keyRight;
	int m_keyDown;
	int m_keyUp;
};