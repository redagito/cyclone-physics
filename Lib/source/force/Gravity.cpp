#include "cyclone/force/Gravity.h"
#include "cyclone/RigidBody.h"

using namespace cyclone;

Gravity::Gravity(const Vector3& gravity)
	: gravity(gravity)
{
}

void Gravity::updateForce(RigidBody* body, double /*duration*/)
{
	// Check that we do not have infinite mass
	if (!body->hasFiniteMass()) return;

	// Apply the mass-scaled force to the body
	body->addForce(gravity * body->getMass());
}