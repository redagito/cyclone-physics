#pragma once

#include "cyclone/Vector3.h"
#include "cyclone/Matrix4.h"

/**
 * @file
 *
 * This file contains the fine grained collision detection system.
 * It is used to return contacts between pairs of primitives.
 *
 * There are two groups of tests in this file. Intersection tests
 * use the fastest separating axis method to check if two objects
 * intersect, and the collision tests generate the contacts. The
 * collision tests typically use the intersection tests as an early
 * out.
 */
namespace cyclone
{
	class RigidBody;

	/**
	 * Represents a primitive to detect collisions against.
	 */
	class CollisionPrimitive
	{
	public:
		virtual ~CollisionPrimitive() = default;

		/**
		 * This class exists to help the collision detector
		 * and intersection routines, so they should have
		 * access to its data.
		 */
		friend class IntersectionTests;
		friend class CollisionDetector;

		/**
		 * The rigid body that is represented by this primitive.
		 */
		RigidBody* body = nullptr;

		/**
		 * The offset of this primitive from the given rigid body.
		 */
		Matrix4 offset;

		/**
		 * Calculates the internals for the primitive.
		 */
		void calculateInternals() const;

		/**
		 * This is a convenience function to allow access to the
		 * axis vectors in the transform for this primitive.
		 */
		Vector3 getAxis(unsigned index) const;

		/**
		 * Returns the resultant transform of the primitive, calculated from
		 * the combined offset of the primitive and the transform
		 * (orientation + position) of the rigid body to which it is
		 * attached.
		 */
		const Matrix4& getTransform() const;


	protected:
		/**
		 * The resultant transform of the primitive. This is
		 * calculated by combining the offset of the primitive
		 * with the transform of the rigid body.
		 */
		mutable Matrix4 transform;
	};
}