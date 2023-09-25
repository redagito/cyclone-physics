#include "cyclone/force/Spring.h"

#include "cyclone/RigidBody.h"

using namespace cyclone;

Spring::Spring(const Vector3& localConnectionPt,
	RigidBody* other,
	const Vector3& otherConnectionPt,
	double springConstant,
	double restLength)
	: connectionPoint(localConnectionPt),
	otherConnectionPoint(otherConnectionPt),
	other(other),
	springConstant(springConstant),
	restLength(restLength)
{
}

void Spring::updateForce(RigidBody* body, double /*duration*/)
{
	// Calculate the two ends in world space
	Vector3 lws = body->getPointInWorldSpace(connectionPoint);
	Vector3 ows = other->getPointInWorldSpace(otherConnectionPoint);

	// Calculate the vector of the spring
	Vector3 force = lws - ows;

	// Calculate the magnitude of the force
	double magnitude = force.magnitude();
	// BUG
	// magnitude = std::abs(magnitude - restLength);
	magnitude = magnitude - restLength;
	magnitude *= springConstant;

	// Calculate the final force and apply it
	force.normalise();
	force *= -magnitude;
	body->addForceAtPoint(force, lws);
}