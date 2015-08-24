/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the entity class				
*			this header is required for all classes that inherit from it:
*			Bullet, Enemy, EnemyBullet, Player
**/

#pragma once

class Entity
{
protected:
	//x and y positions for entities
	float m_x;
	float m_y;

	//entity health
	int m_health;
	//is entity alive
	bool m_alive;
	//is entity to be deleted
	bool m_delete;

	//width and height of entity sprite
	int m_width;
	int m_height;

	//texture of the entity
	int m_texture;


public:
	Entity();

	//draw the entity
	void Draw();

	//returns x and y pos of entity
	float GetX() const;
	float GetY() const;

	//returns width and height of the entity
	int GetWidth() const;
	int GetHeight() const;

	//sets entity alive status
	void SetAlive(const bool alive);
	//reutrns alive status
	bool GetAlive() const;

	//returns pointer to health
	int* GetHealthPtr();

	//returns value of health
	int GetHealth() const;

	//increases the health
	void IncreaseHealth(const int health);

	//sets delete status
	void SetDelete(const bool d);
	//returns delete status
	bool GetDelete() const;
};