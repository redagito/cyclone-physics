#include "cyclone/collision/CollisionPrimitive.h"
#include "cyclone/RigidBody.h"

using namespace cyclone;

void CollisionPrimitive::calculateInternals() const
{
	transform = body->getTransform() * offset;
}

Vector3 CollisionPrimitive::getAxis(unsigned index) const
{
	return getTransform().getAxisVector(index);
}

const Matrix4& CollisionPrimitive::getTransform() const
{
	calculateInternals();
	return transform;
}