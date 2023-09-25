#include "BlobForceGenerator.h"

#include "Constants.h"

void BlobForceGenerator::updateForce(cyclone::Particle* particle,
	double duration)
{
	unsigned joinCount = 0;
	for (unsigned i = 0; i < BLOB_COUNT; i++)
	{
		// Don't attract yourself
		if (particles + i == particle) continue;

		// Work out the separation distance
		cyclone::Vector3 separation =
			particles[i].getPosition() - particle->getPosition();
		separation.z = 0.0f;
		double distance = separation.magnitude();

		if (distance < minNaturalDistance)
		{
			// Use a repulsion force.
			distance = 1.0f - distance / minNaturalDistance;
			particle->addForce(
				separation.unit() * (1.0f - distance) * maxReplusion * -1.0f
			);
			joinCount++;
		}
		else if (distance > maxNaturalDistance && distance < maxDistance)
		{
			// Use an attraction force.
			distance =
				(distance - maxNaturalDistance) /
				(maxDistance - maxNaturalDistance);
			particle->addForce(
				separation.unit() * distance * maxAttraction
			);
			joinCount++;
		}
	}

	// If the particle is the head, and we've got a join count, then float it.
	if (particle == particles && joinCount > 0 && maxFloat > 0)
	{
		double force = double(joinCount / maxFloat) * floatHead;
		if (force > floatHead) force = floatHead;
		particle->addForce(cyclone::Vector3(0, force, 0));
	}
}