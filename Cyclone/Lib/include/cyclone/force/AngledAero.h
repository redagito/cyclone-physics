#pragma once

#include "cyclone/force/Aero.h"

namespace cyclone
{
	/**
	 * A force generator with an aerodynamic surface that can be
	 * re-oriented relative to its rigid body. This derives the
	 */
	class AngledAero : public Aero
	{
		/**
		 * Holds the orientation of the aerodynamic surface relative
		 * to the rigid body to which it is attached.
		 */
		Quaternion orientation;

	public:
		/**
		 * Creates a new aerodynamic surface with the given properties.
		 */
		AngledAero(const Matrix3& tensor, const Vector3& position,
			const Vector3* windspeed);

		/**
		 * Sets the relative orientation of the aerodynamic surface,
		 * relative to the rigid body it is attached to. Note that
		 * this doesn't affect the point of connection of the surface
		 * to the body.
		 */
		void setOrientation(const Quaternion& quat);

		/**
		 * Applies the force to the given rigid body.
		 */
		virtual void updateForce(RigidBody* body, double duration);
	};
}