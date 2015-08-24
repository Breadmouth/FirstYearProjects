#pragma once

class Entity
{
protected:
	float m_x;
	float m_y;

	int m_health;

	bool m_alive;

	int m_width;
	int m_height;

	int m_texture;

public:
	Entity();

	void Draw();

	float GetX();
	float GetY();

	int GetWidth();
	int GetHeight();

	void SetAlive(bool alive);
	bool GetAlive();
};