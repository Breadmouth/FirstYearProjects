#pragma once

#include "GameState.h"
#include "Vec2.h"
#include <vector>

class Sprite;
class Tank;
class Turret;
class BulletManager;
class ParticleManager;
class GraphManager;
class Game;
class Graph;
class GraphNode;
class Vector2;

class PlayingGameState: public GameState
{
protected:
	Sprite* m_tank;
	Sprite* m_turret;
	Sprite* m_healthPack;
	Tank* m_tank2;
	Turret* m_turret2;
	Sprite* m_background;
	BulletManager* m_bulletManager;
	ParticleManager* m_particleManager;
	Graph* m_graph;

	Vector2 m_aiPos;
	
	float m_healthPackSpawn;
	bool m_debug;
	bool m_pathMode;
	Game* m_game;
public:
	PlayingGameState(Game* game);
	~PlayingGameState();

	virtual void Update(float deltaTime);
	virtual void Draw(float deltaTime);
	virtual void Init();
	virtual void Init(unsigned int width, unsigned int height, const char* title);
	virtual void Deinit();

	void FindPath(GraphNode* start, GraphNode* end);

	void CreateGraph(int width, int height);
};