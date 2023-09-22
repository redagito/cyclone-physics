#pragma once

#include "cyclone/force/ForceGenerator.h"
#include "cyclone/Vector3.h"

namespace cyclone
{

	/**
	 * A force generator to apply a buoyant force to a rigid body.
	 */
	class Buoyancy : public ForceGenerator
	{
		/**
		 * The maximum submersion depth of the object before
		 * it generates its maximum buoyancy force.
		 */
		real maxDepth;

		/**
		 * The volume of the object.
		 */
		real volume;

		/**
		 * The height of the water plane above y=0. The plane will be
		 * parallel to the XZ plane.
		 */
		real waterHeight;

		/**
		 * The density of the liquid. Pure water has a density of
		 * 1000kg per cubic meter.
		 */
		real liquidDensity;

		/**
		 * The centre of buoyancy of the rigid body, in body coordinates.
		 */
		Vector3 centreOfBuoyancy;

	public:

		/** Creates a new buoyancy force with the given parameters. */
		Buoyancy(const Vector3& cOfB,
			real maxDepth, real volume, real waterHeight,
			real liquidDensity = 1000.0f);

		/**
		 * Applies the force to the given rigid body.
		 */
		virtual void updateForce(RigidBody* body, real duration);
	};
}