#include "cyclone/force/Buoyancy.h"
#include "cyclone/RigidBody.h"

using namespace cyclone;

Buoyancy::Buoyancy(const Vector3& cOfB, double maxDepth, double volume,
	double waterHeight, double liquidDensity /* = 1000.0f */)
{
	centreOfBuoyancy = cOfB;
	Buoyancy::liquidDensity = liquidDensity;
	Buoyancy::maxDepth = maxDepth;
	Buoyancy::volume = volume;
	Buoyancy::waterHeight = waterHeight;
}

void Buoyancy::updateForce(RigidBody* body, double /*duration*/)
{
	// Calculate the submersion depth
	Vector3 pointInWorld = body->getPointInWorldSpace(centreOfBuoyancy);
	double depth = pointInWorld.y;

	// Check if we're out of the water
	if (depth >= waterHeight + maxDepth) return;
	Vector3 force(0, 0, 0);

	// Check if we're at maximum depth
	if (depth <= waterHeight - maxDepth)
	{
		force.y = liquidDensity * volume;
		body->addForceAtBodyPoint(force, centreOfBuoyancy);
		return;
	}

	// Otherwise we are partly submerged
	force.y = liquidDensity * volume *
		(depth - maxDepth - waterHeight) / 2 * maxDepth;
	body->addForceAtBodyPoint(force, centreOfBuoyancy);
}