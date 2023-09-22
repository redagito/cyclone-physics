#include "cyclone/particle/ParticleSpring.h"

#include "cyclone/Vector3.h"
#include "cyclone/particle/Particle.h"

using namespace cyclone;

ParticleSpring::ParticleSpring(Particle* other, real sc, real rl)
	: other(other), springConstant(sc), restLength(rl)
{
}

void ParticleSpring::updateForce(Particle* particle, real /*duration*/)
{
	// Calculate the vector of the spring
	Vector3 force;
	particle->getPosition(&force);
	force -= other->getPosition();

	// Calculate the magnitude of the force
	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force and apply it
	force.normalise();
	force *= -magnitude;
	particle->addForce(force);
}