#include "Graph.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "Game.h"
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>

Graph::Graph(Game* game)
{
	m_game = game;
	m_path = new vector<GraphNode*>;
}

Graph::~Graph()
{
	while (!m_path->empty())
	{
		GraphNode* node = m_path->back();
		m_path->pop_back();
		delete node;
	}
	delete m_path;
}

void Graph::AddNode(GraphNode* node)
{
	m_nodes.push_back(node);
}

void Graph::RemoveNode(GraphNode* node)
{
	for ( int i = 0; i < m_nodes.size(); i++)
	{
		for ( int j = 0; j < m_nodes[i]->GetEdges().size(); j++)
		{
			//check edges & delete matching
			if ( m_nodes[i]->GetEdges()[j]->To == node)
			{
				m_nodes[i]->RemoveEdge(m_nodes[i]->GetEdges()[j]);
			}
		}
	}

	//delete node
	auto i = std::find(m_nodes.begin(), m_nodes.end(), node);
	m_nodes.erase(i);
	node->~GraphNode();
	
}

GraphNode* Graph::GetFirstNode() const
{
	if(m_nodes.size() > 0)
	{
		return m_nodes.front();
	}
	return nullptr;
}

GraphNode* Graph::GetRandomNode() const
{
	float randomNo = (rand() % m_nodes.size());
	return m_nodes[randomNo];
}

vector<GraphNode*> Graph::GetNodes()	const
{
	return m_nodes;
}

bool Graph::SearchDJK(GraphNode* start, GraphNode* end)
{
	std::vector<GraphNode*> open;
	std::vector<GraphNode*> closed;
	std::map<GraphNode*, GraphNode*> parent;
	std::map<GraphNode*, float> runningCost;

	open.push_back(start);
	runningCost[start] = 0;

	while (!open.empty())
	{
		//choose item with lowest gScore
		GraphNode* current;
		float lowestG = runningCost[open[0]];
		current = open[0];
		for (int  i = 0; i < open.size(); i++)
		{
			if ( runningCost[open[i]] < lowestG)
			{
				lowestG = runningCost[open[i]];
				current = open[i];
			}
		}

		//close node and pop from queue
		closed.push_back(current);
		auto i = std::find(open.begin(), open.end(), current);
		if (i != open.end())
			open.erase(i);


		//check if current node == end node
		if ( current == end )
		{
			m_path->push_back(ReconstructPath(parent, end));
			m_path->push_back(end);
			return true;
		}

		//add children to open stack
		for ( int j = 0; j < current->GetEdges().size(); j++)
		{
			GraphNode* child = current->GetEdges()[j]->To;

			if (!(std::find(closed.begin(), closed.end(), child) != closed.end()))//does this work
			{
				float childRunningCost = current->GetEdges()[j]->Weight + runningCost[current];

				if ( std::find(open.begin(), open.end(), child) != open.end())
				{
					auto i = std::find(open.begin(), open.end(), child);

					if (childRunningCost < runningCost[(*i)])
					{
						open.erase(i);
						runningCost[child] = childRunningCost;
						parent[child] = current;
						open.push_back(child);
					}
				}
				else
				{
					runningCost[child] = childRunningCost;
					parent[child] = current;
					open.push_back(child);
				}
			}
		}
	}
	return false;
}

bool Graph::SearchAStar(GraphNode* start, GraphNode* end)
{
	std::vector<GraphNode*> open;
	std::vector<GraphNode*> closed;
	std::map<GraphNode*, GraphNode*> parent;
	std::map<GraphNode*, float> gScore;
	std::map<GraphNode*, float> fScore;

	open.push_back(start);
	gScore[start] = 0;
	Vector2 heuristicEstimate = end->GetPosition() - start->GetPosition();
	fScore[start] = gScore[start] + heuristicEstimate.GetLength();

	while (!open.empty())
	{
		//choose item with lowest Score
		GraphNode* current;
		float lowestF = fScore[open[0]];
		current = open[0];
		for (int  i = 0; i < open.size(); i++)
		{
			if ( fScore[open[i]] < lowestF)
			{
				heuristicEstimate = end->GetPosition() - open[i]->GetPosition();
				lowestF = gScore[open[i]] + heuristicEstimate.GetLength();
				current = open[i];
			}
		}

		//close node and pop from queue
		closed.push_back(current);
		auto i = std::find(open.begin(), open.end(), current);
		if (i != open.end())
			open.erase(i);


		//check if current node == end node
		if ( current == end )
		{
			m_path->push_back(ReconstructPath(parent, end));
			m_path->push_back(end);
			return true;
		}

		//add children to open stack
		for ( int j = 0; j < current->GetEdges().size(); j++)
		{
			GraphNode* child = current->GetEdges()[j]->To;
			heuristicEstimate = end->GetPosition() - child->GetPosition();

			if (!(std::find(closed.begin(), closed.end(), child) != closed.end()))
			{
				float childGScore = current->GetEdges()[j]->Weight + gScore[current];
				float childFScore = childGScore + heuristicEstimate.GetLength();

				if ( std::find(open.begin(), open.end(), child) != open.end())
				{
					auto i = std::find(open.begin(), open.end(), child);

					if (childFScore < fScore[(*i)])
					{
						open.erase(i);
						gScore[child] = childGScore;
						fScore[child] = childFScore;
						parent[child] = current;
						open.push_back(child);
					}
				}
				else
				{
					gScore[child] = childGScore;
					fScore[child] = childFScore;
					parent[child] = current;
					open.push_back(child);
				}
			}
		}
	}
	return false;
}

GraphNode* Graph::ReconstructPath(map<GraphNode*, GraphNode*> from, GraphNode* to)
{
	auto itr = from.find(to);

	if (itr != from.end())
	{
		itr = from.find(from[to]);
		if ( itr != from.end())
			m_path->push_back(ReconstructPath( from, from[to]));
		return from[to];
	}
	else
	{
		return to;
	}
}

void Graph::EmptyPath()
{
	while (!m_path->empty())
	{
		m_path->pop_back();
	}
}


vector<GraphNode*> Graph::GetPath() const
{
	return *m_path;
}

void Graph::PopPathFront()
{
	auto i = find( m_path->begin(), m_path->end(), m_path->front());
	m_path->erase(i);
}


void Graph::CreateGraph(int width, int height)
{
	//width = number of columns
	//height = number of rows

	for (int i = 1; i < width + 1; i++)
	{
		for (int j = 1; j < height + 1; j++)
		{
			//create a new node on the heap
			GraphNode* node = new GraphNode(Vector2((m_game->GetScreenWidth() / (width + 1)) * i,
													(m_game->GetScreenHeight() / (height + 1)) * j));
			//push the node into the vector (m_nodes)
			m_nodes.push_back(node);
		}
	}

	//determines the max distance that 2 nodes must be from each other in order to connect
	float radius = sqrt(((m_game->GetScreenHeight() / height + 1) * (m_game->GetScreenHeight() / height + 1)) 
						+ ((m_game->GetScreenWidth() / width + 1) * (m_game->GetScreenWidth() / width + 1)));

	for (int i = 0; i < m_nodes.size(); i++)
	{
		for (int j = 0; j < m_nodes.size(); j++)
		{
			//find the distance between two nodes
			Vector2 distance = m_nodes[i]->GetPosition() - m_nodes[j]->GetPosition();
			//check if the two nodes are within connecting distance
			if ( distance.GetLength() < radius && j != i)
			{
				//creates a new edge
				GraphEdge* edge = new GraphEdge();
				//sets the edge data
				edge->From = m_nodes[i];
				edge->To = m_nodes[j];
				edge->Weight = distance.GetLength();
				//pushes the edge into the nodes vector (m_edges)
				m_nodes[i]->AddEdge(edge);
				m_edges.push_back(edge);
			}
		}
	}
}

void Graph::Draw(float deltaTime)
{
	for (int i = 0; i < m_edges.size(); i++)
	{
		m_edges[i]->DrawLine(m_edges[i]->To->GetPosition(), m_edges[i]->From->GetPosition());
	}
}

void Graph::Update(float deltaTime)
{

}
