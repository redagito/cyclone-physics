#include "Platform.h"

#include "Constants.h"

unsigned Platform::addContact(cyclone::ParticleContact* contact,
	unsigned limit) const
{
	const static double restitution = 0.0f;

	unsigned used = 0;
	for (unsigned i = 0; i < BLOB_COUNT; i++)
	{
		if (used >= limit) break;

		// Check for penetration
		cyclone::Vector3 toParticle = particles[i].getPosition() - start;
		cyclone::Vector3 lineDirection = end - start;
		double projected = toParticle * lineDirection;
		double platformSqLength = lineDirection.squareMagnitude();
		if (projected <= 0)
		{
			// The blob is nearest to the start point
			if (toParticle.squareMagnitude() < BLOB_RADIUS * BLOB_RADIUS)
			{
				// We have a collision
				contact->contactNormal = toParticle.unit();
				contact->contactNormal.z = 0;
				contact->restitution = restitution;
				contact->particle[0] = particles + i;
				contact->particle[1] = 0;
				contact->penetration = BLOB_RADIUS - toParticle.magnitude();
				used++;
				contact++;
			}

		}
		else if (projected >= platformSqLength)
		{
			// The blob is nearest to the end point
			toParticle = particles[i].getPosition() - end;
			if (toParticle.squareMagnitude() < BLOB_RADIUS * BLOB_RADIUS)
			{
				// We have a collision
				contact->contactNormal = toParticle.unit();
				contact->contactNormal.z = 0;
				contact->restitution = restitution;
				contact->particle[0] = particles + i;
				contact->particle[1] = 0;
				contact->penetration = BLOB_RADIUS - toParticle.magnitude();
				used++;
				contact++;
			}
		}
		else
		{
			// the blob is nearest to the middle.
			double distanceToPlatform =
				toParticle.squareMagnitude() -
				projected * projected / platformSqLength;
			if (distanceToPlatform < BLOB_RADIUS * BLOB_RADIUS)
			{
				// We have a collision
				cyclone::Vector3 closestPoint =
					start + lineDirection * (projected / platformSqLength);

				contact->contactNormal = (particles[i].getPosition() - closestPoint).unit();
				contact->contactNormal.z = 0;
				contact->restitution = restitution;
				contact->particle[0] = particles + i;
				contact->particle[1] = 0;
				contact->penetration = BLOB_RADIUS - std::sqrt(distanceToPlatform);
				used++;
				contact++;
			}
		}
	}
	return used;
}