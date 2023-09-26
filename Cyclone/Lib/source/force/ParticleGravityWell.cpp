#include "cyclone/force/ParticleGravityWell.h"

#include "cyclone/Particle.h"

using namespace cyclone;

ParticleGravityWell::ParticleGravityWell(double force, const Vector3& position, float deadZoneRadius)
    : force(force), position(position), deadZoneRadius(deadZoneRadius)
{
}

void ParticleGravityWell::updateForce(Particle* particle, double /*duration*/)
{
    // Check that we do not have infinite mass
    if (!particle->hasFiniteMass()) return;

    // Apply the mass-scaled force to the particle
    auto direction = position - particle->getPosition();
    auto distance = direction.magnitude();

    if (distance <= deadZoneRadius) return;
    
    direction.normalise();
    auto gravitationalForce = force * particle->getMass() / (distance * distance);
    particle->addForce(direction * gravitationalForce);
}