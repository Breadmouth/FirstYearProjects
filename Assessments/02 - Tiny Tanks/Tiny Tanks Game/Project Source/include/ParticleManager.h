#pragma once
#include <vector>
#include "Particle.h"
#include "Vec2.h"

class Game;

class ParticleManager
{
public:
	ParticleManager(Game* game);
	~ParticleManager();

	void AddParticle(Vector2 position);
	void Update(float deltaTime);
	void Draw(float deltaTime);

	std::vector<Particle*>* GetParticles();

protected:
	Particle* m_particle;
	std::vector<Particle*> m_particles;

	Game* m_game;
};