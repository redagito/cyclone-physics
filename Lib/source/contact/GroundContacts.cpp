#include "cyclone/contact/GroundContacts.h"
#include "cyclone/contact/ParticleContact.h"
#include "cyclone/Particle.h"

using namespace cyclone;

void GroundContacts::init(Particles* parts)
{
	particles = parts;
}

unsigned GroundContacts::addContact(cyclone::ParticleContact* contact,
	unsigned limit) const
{
	unsigned count = 0;
	for (Particles::iterator p = particles->begin(); p != particles->end(); p++)
	{
		cyclone::real y = (*p)->getPosition().y;
		if (y < 0.0f)
		{
			contact->contactNormal = cyclone::Vector3::UP;
			contact->particle[0] = *p;
			contact->particle[1] = NULL;
			contact->penetration = -y;
			contact->restitution = 0.2f;
			contact++;
			count++;
		}

		if (count >= limit) return count;
	}
	return count;
}