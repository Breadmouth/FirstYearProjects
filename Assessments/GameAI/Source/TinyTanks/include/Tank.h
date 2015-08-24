#pragma once
#include "Sprite.h"
#include <vector>

class Game;
class GraphNode;

class Tank : public Sprite
{
public:
	Tank();
	Tank(Game* game, const char* textureName, int width, int height, 
		Vector2 pos, int up, int down, int left, int right);
	Tank(Game* game, const char* textureName, int width, int height, 
		Vector2 pos);

	void Update(float deltaTime);
	GraphNode* SnapToNode(std::vector<GraphNode*> nodes);
	bool PathToNode(Vector2 destination);

	void AddHealth( int ammount);
	int GetHealth();

	bool GetSearching();
	void SetSearching(bool searching);

	void AddToRotation(float angle);

private:
	int m_keyLeft;
	int m_keyRight;
	int m_keyDown;
	int m_keyUp;

	int m_health;
	bool m_searching;

	bool m_ai;
	Vector2 m_destination;
};