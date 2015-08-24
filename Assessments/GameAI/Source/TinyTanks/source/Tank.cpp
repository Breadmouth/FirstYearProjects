#include "Tank.h"
#include "Game.h"
#include "GraphNode.h"
#include "Vec2.h"
#include <math.h>

Tank::Tank(Game* game, const char* textureName, int width, int height, Vector2 pos, int up, int down, int left, int right)
	: Sprite(game, textureName, width, height)
{
	m_game = game;
	Init();
	LoadTexture(textureName);
	m_width = width;
	m_height = height;
	m_position = pos;
	m_anchor = Vector2(0.5, 0.5);
	if (height > width)
		m_radius = (float)height / 2.0f;
	else
		m_radius = (float)width / 2.0f;

	m_keyLeft = left;
	m_keyRight = right;
	m_keyUp = up;
	m_keyDown = down;

	m_ai = false;
	m_health = 100;
}

Tank::Tank(Game* game, const char* textureName, int width, int height, Vector2 pos)
	: Sprite(game, textureName, width, height)
{
	m_game = game;
	Init();
	LoadTexture(textureName);
	m_width = width;
	m_height = height;
	m_position = pos;
	m_anchor = Vector2(0.5, 0.5);
	if (height > width)
		m_radius = (float)height / 2.0f;
	else
		m_radius = (float)width / 2.0f;

	m_ai = true;
	m_searching = false;
	m_health = 100;
}

void Tank::Update(float deltaTime)
{
	m_previousPosition = m_position;

	if ( !m_ai )
	{
		if (glfwGetKey(m_game->GetWindow(), m_keyLeft))
		{
			m_rotation -= 0.5f * deltaTime;
		}
		if (glfwGetKey(m_game->GetWindow(), m_keyRight))
		{
			m_rotation += 0.5f * deltaTime;
		}
		if (glfwGetKey(m_game->GetWindow(), m_keyDown))
		{
			m_position -= Vector2( sin(m_rotation), cos(m_rotation)) * 80 * deltaTime;

		}
		if (glfwGetKey(m_game->GetWindow(), m_keyUp))
		{
			m_position += Vector2( sin(m_rotation), cos(m_rotation)) * 80 * deltaTime;
		}
	}
	else
	{
		if (!(m_position.x <= m_destination.x + 5 &&  m_position.x >= m_destination.x - 5 && m_position.y <= m_destination.y + 5 &&  m_position.y >= m_destination.y - 5))
		{
			//m_destination = m_destination - m_position;
			//m_destination.Normalise();
			//m_rotation = atan2f(m_destination.x, m_destination.y);
			m_position += Vector2( sin(m_rotation), cos(m_rotation)) * 80 * deltaTime;
		}
	}

	Sprite::Update(deltaTime);
}

void Tank::AddHealth( int ammount)
{
	m_health += ammount;
	if (m_health > 100)
		m_health = 100;
	if (m_health < 0)
		m_health = 0;
}

int Tank::GetHealth()
{
	return m_health;
}

GraphNode* Tank::SnapToNode(std::vector<GraphNode*> nodes)
{ 
	float distance = 9999;
	GraphNode* closestNode;
	Vector2 spaceBetween;

	for (int i = 0; i < nodes.size(); i++)
	{
		spaceBetween = m_position - nodes[i]->GetPosition();
		if ( spaceBetween.GetLength() < distance )
		{
			distance = spaceBetween.GetLength();
			closestNode = nodes[i];
		}
	}

	m_destination = closestNode->GetPosition();
	return closestNode;
}

bool Tank::PathToNode(Vector2 destination)
{
	if (!(m_destination == destination))
	{
		m_destination = destination;
		return false;
	}
	return true;
}

bool Tank::GetSearching()
{
	return m_searching;
}

void Tank::SetSearching(bool searching)
{
	m_searching = searching;
}
void Tank::AddToRotation(float angle)
{
	m_rotation += angle;
}
