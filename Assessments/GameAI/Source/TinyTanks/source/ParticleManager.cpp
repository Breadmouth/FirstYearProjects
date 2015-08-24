#include "ParticleManager.h"
#include "Game.h"
#include <stdlib.h>
#include <time.h>

ParticleManager::ParticleManager(Game* game)
{
	m_game = game;
	srand(GetCurrentTime());
}

ParticleManager::~ParticleManager()
{
	for ( auto i = m_particles.begin(); i != m_particles.end(); )
	{
		(i) = m_particles.erase(i);
		delete (*i);
	}
	delete m_particle;
}

void ParticleManager::AddParticle(Vector2 position)
{
	m_particle = new Particle( m_game, "Red.png", 3, 3);
	m_particle->SetPosition( position.x, position.y);
	m_particle->SetRotation((float)rand());
	m_particles.push_back(m_particle);
}

void ParticleManager::Update(float deltaTime)
{

	for ( auto i = m_particles.begin(); i != m_particles.end(); i++)
	{
		(*i)->Update(deltaTime);
	}

	auto i = m_particles.begin();
	while (i != m_particles.end())
	{
		if ((*i)->GetAlive() == false)

		{
			delete (*i);
			i = m_particles.erase(i);
		}
		else
		{
			i++;
		}
	}

}

void ParticleManager::Draw(float deltaTime)
{
	for ( auto i = m_particles.begin(); i != m_particles.end(); i++)
	{
		(*i)->Draw(deltaTime);
	}
}

std::vector<Particle*>* ParticleManager::GetParticles()
{
	return &m_particles;
}
