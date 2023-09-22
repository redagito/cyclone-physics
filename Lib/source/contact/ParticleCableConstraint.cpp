#include "cyclone/contact/ParticleCableConstraint.h"
#include "cyclone/contact/ParticleContact.h"
#include "cyclone/Particle.h"

using namespace cyclone;

unsigned ParticleCableConstraint::addContact(ParticleContact* contact,
	unsigned /*limit*/) const
{
	// Find the length of the cable
	real length = currentLength();

	// Check if we're over-extended
	if (length < maxLength)
	{
		return 0;
	}

	// Otherwise return the contact
	contact->particle[0] = particle;
	contact->particle[1] = nullptr;

	// Calculate the normal
	Vector3 normal = anchor - particle->getPosition();
	normal.normalise();
	contact->contactNormal = normal;

	contact->penetration = length - maxLength;
	contact->restitution = restitution;

	return 1;
}