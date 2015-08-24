#include "GraphNode.h"
#include "GraphEdge.h"
#include "Vec2.h"

GraphNode::GraphNode(Vector2 position)
{
	m_position = position;
}

GraphNode::~GraphNode()
{
	//remove all edges first
	for (auto i = m_edges.begin(); i != m_edges.end(); i++)
	{
		(i) = m_edges.erase(i);
		delete (*i);
	}
}

Vector2 GraphNode::GetPosition()	const
{
	return m_position;
}

void GraphNode::AddEdge(GraphEdge* edge)
{
	m_edges.push_back(edge);
}

void GraphNode::RemoveEdge(GraphEdge* edge)
{
	auto i = std::find(m_edges.begin(), m_edges.end(), edge);
	m_edges.erase(i);
}

vector<GraphEdge*> GraphNode::GetEdges()
{
	return m_edges;
}