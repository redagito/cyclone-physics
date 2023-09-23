#include "cyclone/force/ParticleSpring.h"

#include "cyclone/Vector3.h"
#include "cyclone/Particle.h"

using namespace cyclone;

ParticleSpring::ParticleSpring(Particle* other, double sc, double rl)
	: other(other), springConstant(sc), restLength(rl)
{
}

void ParticleSpring::updateForce(Particle* particle, double /*duration*/)
{
	// Calculate the vector of the spring
	Vector3 force;
	particle->getPosition(&force);
	force -= other->getPosition();

	// Calculate the magnitude of the force
	double magnitude = force.magnitude();
	magnitude = std::abs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force and apply it
	force.normalise();
	force *= -magnitude;
	particle->addForce(force);
}