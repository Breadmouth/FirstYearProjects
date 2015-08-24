#include "HealthPack.h"

HealthPack::HealthPack(Game* game, const char* textureName, int width, int height, Vector2 pos)
	: Sprite(game, textureName, width, height) 
{
	m_game = game;
	Init();
	LoadTexture(textureName);
	m_width = width;
	m_height = height;
	m_position = pos;
	m_anchor = Vector2(0.5, 0.5);
}

void HealthPack::Update(float deltaTime)
{
	Sprite::Update(deltaTime);
}