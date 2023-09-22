#include "cyclone/contact/ParticleRodConstraint.h"
#include "cyclone/contact/ParticleContact.h"
#include "cyclone/Particle.h"

using namespace cyclone;

unsigned ParticleRodConstraint::addContact(ParticleContact* contact,
	unsigned /*limit*/) const
{
	// Find the length of the rod
	real currentLen = currentLength();

	// Check if we're over-extended
	if (currentLen == length)
	{
		return 0;
	}

	// Otherwise return the contact
	contact->particle[0] = particle;
	contact->particle[1] = nullptr;

	// Calculate the normal
	Vector3 normal = anchor - particle->getPosition();
	normal.normalise();

	// The contact normal depends on whether we're extending or compressing
	if (currentLen > length) {
		contact->contactNormal = normal;
		contact->penetration = currentLen - length;
	}
	else {
		contact->contactNormal = normal * -1;
		contact->penetration = length - currentLen;
	}

	// Always use zero restitution (no bounciness)
	contact->restitution = 0;

	return 1;
}