#pragma once

#include "cyclone/force/ForceGenerator.h"
#include "cyclone/Vector3.h"

namespace cyclone
{

	/**
	 * A force generator that applies a Spring force.
	 */
	class Spring : public ForceGenerator
	{
		/**
		 * The point of connection of the spring, in local
		 * coordinates.
		 */
		Vector3 connectionPoint;

		/**
		 * The point of connection of the spring to the other object,
		 * in that object's local coordinates.
		 */
		Vector3 otherConnectionPoint;

		/** The particle at the other end of the spring. */
		RigidBody* other;

		/** Holds the sprint constant. */
		double springConstant;

		/** Holds the rest length of the spring. */
		double restLength;

	public:

		/** Creates a new spring with the given parameters. */
		Spring(const Vector3& localConnectionPt,
			RigidBody* other,
			const Vector3& otherConnectionPt,
			double springConstant,
			double restLength);

		/** Applies the spring force to the given rigid body. */
		virtual void updateForce(RigidBody* body, double duration);
	};
}