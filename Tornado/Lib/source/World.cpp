#include "tornado/World.h"

#include "tornado/Particle.h"

using namespace tornado;

Particle* World::createParticle()
{
	m_particles.push_back(Particle{});
	return &m_particles.back();
}

void World::update(float /*duration*/)
{
	// update forces
}