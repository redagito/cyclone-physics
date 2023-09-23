#include "cyclone/contact/ParticleConstraint.h"
#include "cyclone/Particle.h"

using namespace cyclone;

double ParticleConstraint::currentLength() const
{
	Vector3 relativePos = particle->getPosition() - anchor;
	return relativePos.magnitude();
}