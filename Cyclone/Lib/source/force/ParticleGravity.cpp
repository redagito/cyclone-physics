#include "cyclone/force/ParticleGravity.h"

#include "cyclone/Particle.h"

using namespace cyclone;

ParticleGravity::ParticleGravity(const Vector3& gravity)
    : gravity(gravity)
{
}

void ParticleGravity::updateForce(Particle* particle, double /*duration*/)
{
    // Check that we do not have infinite mass
    if (!particle->hasFiniteMass()) return;

    // Apply the mass-scaled force to the particle
    particle->addForce(gravity * particle->getMass());
}