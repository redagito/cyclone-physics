#include "cyclone/contact/ParticleCable.h"
#include "cyclone/contact/ParticleContact.h"
#include "cyclone/Particle.h"

using namespace cyclone;

unsigned ParticleCable::addContact(ParticleContact* contact,
	unsigned /*limit*/) const
{
	// Find the length of the cable
	double length = currentLength();

	// Check if we're over-extended
	if (length < maxLength)
	{
		return 0;
	}

	// Otherwise return the contact
	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	// Calculate the normal
	Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalise();
	contact->contactNormal = normal;

	contact->penetration = length - maxLength;
	contact->restitution = restitution;

	return 1;
}