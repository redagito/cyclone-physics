#include "cyclone/force/ParticleBungee.h"
#include "cyclone/Particle.h"

using namespace cyclone;

ParticleBungee::ParticleBungee(Particle* other, real sc, real rl)
	: other(other), springConstant(sc), restLength(rl)
{
}

void ParticleBungee::updateForce(Particle* particle, real /*duration*/)
{
	// Calculate the vector of the spring
	Vector3 force;
	particle->getPosition(&force);
	force -= other->getPosition();

	// Check if the bungee is compressed
	real magnitude = force.magnitude();
	if (magnitude <= restLength) return;

	// Calculate the magnitude of the force
	magnitude = springConstant * (restLength - magnitude);

	// Calculate the final force and apply it
	force.normalise();
	force *= -magnitude;
	particle->addForce(force);
}