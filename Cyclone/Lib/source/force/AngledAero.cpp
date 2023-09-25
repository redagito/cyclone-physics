#include "cyclone/force/AngledAero.h"

using namespace cyclone;

/**
 * Creates a new aerodynamic surface with the given properties.
 */
AngledAero::AngledAero(const Matrix3& tensor, const Vector3& position,
	const Vector3* windspeed)
	: Aero(tensor, position, windspeed)
{
	// TODO
}

/**
 * Sets the relative orientation of the aerodynamic surface,
 * relative to the rigid body it is attached to. Note that
 * this doesn't affect the point of connection of the surface
 * to the body.
 */
void AngledAero::setOrientation(const Quaternion& /*quat*/)
{

}

/**
 * Applies the force to the given rigid body.
 */
void AngledAero::updateForce(RigidBody* /*body*/, double /*duration*/)
{

}