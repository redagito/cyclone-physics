#include "cyclone/contact/ParticleRod.h"
#include "cyclone/contact/ParticleContact.h"
#include "cyclone/Particle.h"

using namespace cyclone;

unsigned ParticleRod::addContact(ParticleContact* contact,
	unsigned /*limit*/) const
{
	// Find the length of the rod
	double currentLen = currentLength();

	// TODO Bug?
	// Check if we're over-extended
	if (currentLen == length)
	{
		return 0;
	}

	// Otherwise return the contact
	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	// Calculate the normal
	Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
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