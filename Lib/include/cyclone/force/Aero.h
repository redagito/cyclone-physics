#pragma once

#include "cyclone/force/ForceGenerator.h"
#include "cyclone/Matrix3.h"

namespace cyclone
{
	/**
	 * A force generator that applies an aerodynamic force.
	 */
	class Aero : public ForceGenerator
	{
	protected:
		/**
		 * Holds the aerodynamic tensor for the surface in body
		 * space.
		 */
		Matrix3 tensor;

		/**
		 * Holds the relative position of the aerodynamic surface in
		 * body coordinates.
		 */
		Vector3 position;

		/**
		 * Holds a pointer to a vector containing the windspeed of the
		 * environment. This is easier than managing a separate
		 * windspeed vector per generator and having to update it
		 * manually as the wind changes.
		 */
		const Vector3* windspeed;

	public:
		/**
		 * Creates a new aerodynamic force generator with the
		 * given properties.
		 */
		Aero(const Matrix3& tensor, const Vector3& position,
			const Vector3* windspeed);

		virtual ~Aero() = default;

		/**
		 * Applies the force to the given rigid body.
		 */
		virtual void updateForce(RigidBody* body, double duration);

	protected:
		/**
		 * Uses an explicit tensor matrix to update the force on
		 * the given rigid body. This is exactly the same as for updateForce
		 * only it takes an explicit tensor.
		 */
		void updateForceFromTensor(RigidBody* body, double duration,
			const Matrix3& tensor);
	};
}