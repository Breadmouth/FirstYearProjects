#pragma once

#include <vector>
#include "Vec2.h"

using namespace std;

class GraphEdge;
class Vector2;

class GraphNode
{
protected:
	//your node data goes here
	//could template node class
	Vector2 m_position;
	vector<GraphEdge*> m_edges;
public:
	GraphNode(Vector2 position);
	virtual ~GraphNode();
	void AddEdge(GraphEdge* edge);
	void RemoveEdge(GraphEdge* edge);
	Vector2 GetPosition() const;
	vector<GraphEdge*> GetEdges();
};