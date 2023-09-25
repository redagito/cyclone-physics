#pragma once

#include "cyclone/force/ForceGenerator.h"
#include "cyclone/Vector3.h"

namespace cyclone
{
	/**
	 * A force generator that applies a gravitational force. One instance
	 * can be used for multiple rigid bodies.
	 */
	class Gravity : public ForceGenerator
	{
		/** Holds the acceleration due to gravity. */
		Vector3 gravity;

	public:

		/** Creates the generator with the given acceleration. */
		Gravity(const Vector3& gravity);

		/** Applies the gravitational force to the given rigid body. */
		virtual void updateForce(RigidBody* body, double duration);
	};
}