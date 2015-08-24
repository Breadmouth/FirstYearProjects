#pragma once

#include <vector>
#include <map>

using namespace std;

class GraphNode;
class GraphEdge;
class Game;

class Graph
{
protected:
	vector<GraphNode*> m_nodes;
	vector<GraphEdge*> m_edges;
	vector<GraphNode*>* m_path;
	Game* m_game;

public:
	Graph(Game* game);
	virtual ~Graph();

	void CreateGraph(int width, int height);

	void AddNode(GraphNode* node);
	void RemoveNode(GraphNode* node);
	vector<GraphNode*> GetNodes() const;
	GraphNode* GetFirstNode() const;
	GraphNode* GetRandomNode()	const;

	vector<GraphNode*> GetPath() const;
	void EmptyPath();
	void PopPathFront();

	void Draw(float deltaTime);
	void Update(float deltaTime);

	bool SearchDJK(GraphNode* start, GraphNode* end);
	bool SearchAStar(GraphNode* start, GraphNode* end);
	GraphNode* ReconstructPath(map<GraphNode*, GraphNode*> from, GraphNode* to);
};
