#pragma once

namespace cyclone
{
	class CollisionSphere;
	class CollisionPlane;
	class CollisionData;
	class CollisionBox;
	class Vector3;

	/**
	 * A wrapper class that holds the fine grained collision detection
	 * routines.
	 *
	 * Each of the functions has the same format: it takes the details
	 * of two objects, and a pointer to a contact array to fill. It
	 * returns the number of contacts it wrote into the array.
	 */
	class CollisionDetector
	{
	public:
		CollisionDetector() = delete;
		CollisionDetector(const CollisionDetector&) = delete;
		~CollisionDetector() = delete;

		static unsigned sphereAndHalfSpace(
			const CollisionSphere& sphere,
			const CollisionPlane& plane,
			CollisionData* data
		);

		static unsigned sphereAndTruePlane(
			const CollisionSphere& sphere,
			const CollisionPlane& plane,
			CollisionData* data
		);

		static unsigned sphereAndSphere(
			const CollisionSphere& one,
			const CollisionSphere& two,
			CollisionData* data
		);

		/**
		 * Does a collision test on a collision box and a plane representing
		 * a half-space (i.e. the normal of the plane
		 * points out of the half-space).
		 */
		static unsigned boxAndHalfSpace(
			const CollisionBox& box,
			const CollisionPlane& plane,
			CollisionData* data
		);

		static unsigned boxAndBox(
			const CollisionBox& one,
			const CollisionBox& two,
			CollisionData* data
		);

		static unsigned boxAndPoint(
			const CollisionBox& box,
			const Vector3& point,
			CollisionData* data
		);

		static unsigned boxAndSphere(
			const CollisionBox& box,
			const CollisionSphere& sphere,
			CollisionData* data
		);
	};
}