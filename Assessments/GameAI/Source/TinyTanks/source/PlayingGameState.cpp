#include "PlayingGameState.h"
#include "Tank.h"
#include "Turret.h"
#include "HealthPack.h"
#include "Vec2.h"
#include "Game.h"
#include "ParticleManager.h"
#include "Graph.h"
#include "GraphNode.h"
#include <GLFW/glfw3.h>

PlayingGameState::PlayingGameState(Game* game) : GameState(game->GetGameStateManager()), m_game(game)
{

}

PlayingGameState::~PlayingGameState()
{

}
void PlayingGameState::Init()
{
	Init(800, 600, "Test");
}



void PlayingGameState::Init(unsigned int width, unsigned int height, const char* title)
{
	m_bulletManager = new BulletManager(m_game);
	m_particleManager = new ParticleManager(m_game);

	//pointer to this, width, height, up, down, left right
	m_tank = new Tank(m_game, "Tank2.png", 50, 100, Vector2(100, 300), 'W', 'S', 'A', 'D');
	m_tank2 = new Tank(m_game, "Tank.png", 50, 100, Vector2(700, 300));
	m_turret = new Turret(m_game, m_bulletManager, "Turret.png", 40, 80, 'Q', 'E', GLFW_KEY_SPACE);
	m_turret2 = new Turret(m_game, m_bulletManager, "Turret.png", 40, 80);
	m_background = new Sprite(m_game, "Background.png", m_game->GetScreenWidth(), m_game->GetScreenHeight());
	m_graph = new Graph(m_game);

	m_graph->CreateGraph(8, 8);
	m_tank2->SnapToNode(m_graph->GetNodes());

	m_healthPack = nullptr;

	m_tank->AddChild(m_turret);
	m_tank2->AddChild(m_turret2);

	m_healthPackSpawn = 5.0f;

	m_debug = true;
}

void PlayingGameState::Deinit()
{
	delete m_tank;
	delete m_tank2;
	delete m_turret;
	delete m_turret2;
	delete m_bulletManager;
	delete m_particleManager;
	delete m_background;
	delete m_graph;
	if (m_healthPack != nullptr)
		delete m_healthPack;
}

void PlayingGameState::Draw(float deltaTime)
{
	m_graph->Draw(deltaTime);
	m_background->Draw(deltaTime);
	if (m_debug)
		m_graph->Draw(deltaTime);
	m_tank->Draw(deltaTime);
	m_tank2->Draw(deltaTime);
	m_turret->Draw(deltaTime);
	m_turret2->Draw(deltaTime);
	m_bulletManager->Draw(deltaTime);
	m_particleManager->Draw(deltaTime);
	if (m_healthPack != nullptr)
	{
		m_healthPack->Draw(deltaTime);
	}
}

void PlayingGameState::Update(float deltaTime)
{
	//////////-- ai pathfinding --///////////
	m_aiPos = m_tank2->GetPosition();

	float distance = 9999;
	GraphNode* tank2ClosestNode;
	Vector2 spaceBetween;

	/////////- find GraphNode closest to Tank2 -////////
	for (int i = 0; i < m_graph->GetNodes().size(); i++)
	{
		spaceBetween = m_aiPos - m_graph->GetNodes()[i]->GetPosition();
		if ( spaceBetween.GetLength() < distance )
		{
			distance = spaceBetween.GetLength();
			tank2ClosestNode = m_graph->GetNodes()[i];
		}
	}

	GraphNode* tank1ClosestNode;
	distance = 9999;

	/////////- find GraphNode closest to Tank1 -/////////
	for (int i = 0; i < m_graph->GetNodes().size(); i++)
	{
		spaceBetween = m_tank->GetPosition() - m_graph->GetNodes()[i]->GetPosition();
		if ( spaceBetween.GetLength() < distance )
		{
			distance = spaceBetween.GetLength();
			tank1ClosestNode = m_graph->GetNodes()[i];
		}
	}

	///////- AStar search to mouse on mouse click -////////
	if (glfwGetMouseButton(m_game->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		m_tank2->SetSearching(false);
		m_graph->EmptyPath();
		m_pathMode = false;
		distance = 9999;

		for (int i = 0; i < m_graph->GetNodes().size(); i++)
		{
			double x;
			double y;
			glfwGetCursorPos(m_game->GetWindow(), &x, &y);
			spaceBetween = Vector2( x, m_game->GetScreenHeight() - y ) - m_graph->GetNodes()[i]->GetPosition();
			if ( spaceBetween.GetLength() < distance )
			{
				distance = spaceBetween.GetLength();
				tank1ClosestNode = m_graph->GetNodes()[i];
			}
		}

		FindPath(tank2ClosestNode, tank1ClosestNode);
	}

	/////////////////////////////////////////////////////

	/////////- spawn/update healthpack -//////////
	m_healthPackSpawn -= deltaTime;
	if (m_healthPackSpawn <= 0 && m_healthPack == nullptr)
	{
		m_healthPackSpawn = 5.0f;
		m_healthPack = new HealthPack(m_game, "Health.png", 20, 20, m_graph->GetRandomNode()->GetPosition());
	}

	if (m_healthPack != nullptr)
	{
		m_healthPack->Update(deltaTime);
	}

	/////////- path tank to health if hurt -/////////
	if (!m_tank2->GetSearching() && m_tank2->GetHealth() < 40 && m_healthPack != nullptr)
	{
		m_tank2->SetSearching(true);
		m_graph->EmptyPath();
		m_pathMode = false;
		distance = 9999;

		for (int i = 0; i < m_graph->GetNodes().size(); i++)
		{
			spaceBetween = m_healthPack->GetPosition() - m_graph->GetNodes()[i]->GetPosition();
			if ( spaceBetween.GetLength() < distance )
			{
				distance = spaceBetween.GetLength();
				tank1ClosestNode = m_graph->GetNodes()[i];
			}
		}
		FindPath(tank2ClosestNode, tank1ClosestNode);
	}

		//////////- if there is a path, follow path -////////////
	if ( m_graph->GetPath().size() > 0)
	{
		//if tank is facing the node...
		Vector2 destination = (m_graph->GetPath().front()->GetPosition() - m_tank2->GetPosition());
		Vector2 pos = destination;
		destination.Normalise();
		if (m_tank2->GetRotation() < atan2f(destination.x, destination.y) + 0.1 && m_tank2->GetRotation() > atan2f(destination.x, destination.y) - 0.1)
		{
			m_tank2->SetRotation(atan2f(destination.x,destination.y));
			m_tank2->PathToNode(m_graph->GetPath().front()->GetPosition());
		}
		else
		{
			//rotate tank towards target node

			float angle = atan2f(destination.x,destination.y);
			if (angle > m_tank2->GetRotation())
				m_tank2->AddToRotation(deltaTime);
			else 
				m_tank2->AddToRotation(-deltaTime);

		}
		if ((m_aiPos.x <= m_graph->GetPath().front()->GetPosition().x + 5 &&  m_aiPos.x >= m_graph->GetPath().front()->GetPosition().x - 5 && m_aiPos.y <= m_graph->GetPath().front()->GetPosition().y + 5 &&  m_aiPos.y >= m_graph->GetPath().front()->GetPosition().y - 5))
		{
			m_graph->PopPathFront();
		}
		if (m_tank2->GetRotation() > 3.141592 * 2)
			m_tank2->SetRotation(0);
		else if (m_tank2->GetRotation() < -3.141592 * 2)
			m_tank2->SetRotation(0);
	}
	else
	{
		////////- if no path, path to Tank1 using dijkstra -/////////
		m_pathMode = true;
		m_tank2->SetSearching(false);
		FindPath(tank2ClosestNode, tank1ClosestNode);
	}

	//tank2 - health collision
	if (m_healthPack != nullptr && m_healthPack->GetPosition().x < m_tank2->GetPosition().x + (m_tank2->GetWidth() / 2) && m_healthPack->GetPosition().x > m_tank2->GetPosition().x + (- m_tank2->GetWidth() / 2) && m_healthPack->GetPosition().y < m_tank2->GetPosition().y + (+ m_tank2->GetHeight() / 2) && m_healthPack->GetPosition().y > m_tank2->GetPosition().y + (- m_tank2->GetHeight() / 2))
	{
		m_tank2->SetSearching(false);
		m_tank2->AddHealth(60);
		delete m_healthPack;
		m_healthPack = nullptr;
	}

	m_tank->Update(deltaTime);
	m_tank2->Update(deltaTime);
	m_bulletManager->Update(deltaTime);
	
	//rectangular bounding collision between tanks and bullets && bullets and walls
	
	std::vector<Bullet*>* m_bullets = m_bulletManager->GetBullets();
	Vector3 temp_bullet;
	
	for ( auto i = m_bullets->begin(); i != m_bullets->end(); i++)
	{
		Vector2 pos = (*i)->GetPosition();
		temp_bullet = m_tank->Invert() * pos;
		
		//bullet and tank1
		if (temp_bullet.x < (m_tank->GetWidth() / 2) && temp_bullet.x > (- m_tank->GetWidth() / 2) && temp_bullet.y < (+ m_tank->GetHeight() / 2) && temp_bullet.y > (- m_tank->GetHeight() / 2))
		{
			(*i)->SetAlive(false);
	
			for (int j = 0; j < 10; ++j)
			{
				m_particleManager->AddParticle((*i)->GetPosition());
			}
		}
	
		temp_bullet = m_tank2->Invert() * pos;
		
		//bullet and tank2
		if (temp_bullet.x < (m_tank2->GetWidth() / 2) && temp_bullet.x > (- m_tank2->GetWidth() / 2) && temp_bullet.y < (+ m_tank2->GetHeight() / 2) && temp_bullet.y > (- m_tank2->GetHeight() / 2))
		{
			(*i)->SetAlive(false);
			m_tank2->AddHealth(-20);
	
			for (int j = 0; j < 10; ++j)
			{
				m_particleManager->AddParticle((*i)->GetPosition());
			}
		}
	
		//bullet and wall
		if ((*i)->GetPosition().x > 800 || (*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 600 || (*i)->GetPosition().y < 0)
		{
			(*i)->SetAlive(false);
		}
	}
	
	// circular bounding collision check between tanks
	if (Vector2 (m_tank->GetPosition().x - m_tank2->GetPosition().x, m_tank->GetPosition().y - m_tank2->GetPosition().y).GetLength() < m_tank->GetRadius() + m_tank2->GetRadius())
	{
		m_tank->SetPosition(m_tank->GetPreviousPosition());
		m_tank2->SetPosition(m_tank2->GetPreviousPosition());
	}
	
	//circular collisions between tanks and walls
	if (m_tank->GetPosition().x + m_tank->GetRadius() > m_game->GetScreenWidth() || m_tank->GetPosition().x - m_tank->GetRadius() < 0 || m_tank->GetPosition().y + m_tank->GetRadius() > m_game->GetScreenHeight() || m_tank->GetPosition().y - m_tank->GetRadius() < 0)
		m_tank->SetPosition(m_tank->GetPreviousPosition());
	
	if (m_tank2->GetPosition().x + m_tank2->GetRadius() > m_game->GetScreenWidth() || m_tank2->GetPosition().x - m_tank2->GetRadius() < 0 || m_tank2->GetPosition().y + m_tank2->GetRadius() > m_game->GetScreenHeight() || m_tank2->GetPosition().y - m_tank2->GetRadius() < 0)
		m_tank2->SetPosition(m_tank2->GetPreviousPosition());
		
	//delete bullets that are dead
	for ( auto i = m_bullets->begin(); i != m_bullets->end(); i++)
	{
		if ((*i)->GetAlive() == false)
		{
			m_bullets->erase(i);
			return;
		}
	}
	
	m_particleManager->Update(deltaTime);
}

void PlayingGameState::FindPath(GraphNode* start, GraphNode* end)
{
	if (m_pathMode)
		m_graph->SearchDJK(start ,end); 
	else
		m_graph->SearchAStar(start ,end); 

}
