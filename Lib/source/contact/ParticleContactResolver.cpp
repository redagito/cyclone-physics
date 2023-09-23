#include "cyclone/contact/ParticleContactResolver.h"
#include "cyclone/contact/ParticleContact.h"

#include <cfloat>

using namespace cyclone;

ParticleContactResolver::ParticleContactResolver(unsigned iterations)
	:
	iterations(iterations)
{
}

void ParticleContactResolver::setIterations(unsigned iter)
{
	iterations = iter;
}

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray,
	unsigned numContacts,
	double duration)
{
	for (iterationsUsed = 0; iterationsUsed < iterations; ++iterationsUsed)
	{
		// Find the contact with the largest closing velocity;
		double max = DBL_MAX;
		unsigned maxIndex = numContacts;
		for (unsigned int i = 0; i < numContacts; i++)
		{
			double sepVel = contactArray[i].calculateSeparatingVelocity();
			if (sepVel < max &&
				(sepVel < 0 || contactArray[i].penetration > 0))
			{
				max = sepVel;
				maxIndex = i;
			}
		}

		// Do we have anything worth resolving?
		if (maxIndex == numContacts) break;

		// Resolve this contact
		contactArray[maxIndex].resolve(duration);

		// Update the interpenetrations for all particles
		Vector3* move = contactArray[maxIndex].particleMovement;
		for (unsigned int i = 0; i < numContacts; i++)
		{
			if (contactArray[i].particle[0] == contactArray[maxIndex].particle[0])
			{
				contactArray[i].penetration -= move[0] * contactArray[i].contactNormal;
			}
			else if (contactArray[i].particle[0] == contactArray[maxIndex].particle[1])
			{
				contactArray[i].penetration -= move[1] * contactArray[i].contactNormal;
			}
			if (contactArray[i].particle[1])
			{
				if (contactArray[i].particle[1] == contactArray[maxIndex].particle[0])
				{
					contactArray[i].penetration += move[0] * contactArray[i].contactNormal;
				}
				else if (contactArray[i].particle[1] == contactArray[maxIndex].particle[1])
				{
					contactArray[i].penetration += move[1] * contactArray[i].contactNormal;
				}
			}
		}
	}
}