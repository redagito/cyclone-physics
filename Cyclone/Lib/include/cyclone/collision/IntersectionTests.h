#pragma once

namespace cyclone
{
	class CollisionSphere;
	class CollisionPlane;
	class CollisionBox;

	/**
	 * A wrapper class that holds fast intersection tests. These
	 * can be used to drive the coarse collision detection system or
	 * as an early out in the full collision tests below.
	 */
	class IntersectionTests
	{
	public:
		IntersectionTests() = delete;
		IntersectionTests(const IntersectionTests&) = delete;
		~IntersectionTests() = delete;

		static bool sphereAndHalfSpace(
			const CollisionSphere& sphere,
			const CollisionPlane& plane);

		static bool sphereAndSphere(
			const CollisionSphere& one,
			const CollisionSphere& two);

		static bool boxAndBox(
			const CollisionBox& one,
			const CollisionBox& two);

		/**
		 * Does an intersection test on an arbitrarily aligned box and a
		 * half-space.
		 *
		 * The box is given as a transform matrix, including
		 * position, and a vector of half-sizes for the extend of the
		 * box along each local axis.
		 *
		 * The half-space is given as a direction (i.e. unit) vector and the
		 * offset of the limiting plane from the origin, along the given
		 * direction.
		 */
		static bool boxAndHalfSpace(
			const CollisionBox& box,
			const CollisionPlane& plane);
	};

}