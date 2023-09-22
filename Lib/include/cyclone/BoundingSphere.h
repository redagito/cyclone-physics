#pragma once

#include "cyclone/core.h"
#include "cyclone/Vector3.h"

namespace cyclone
{

	/**
	 * Represents a bounding sphere that can be tested for overlap.
	 */
	class BoundingSphere
	{
		Vector3 centre;
		real radius;

	public:
		/**
		 * Creates a new bounding sphere at the given centre and radius.
		 */
		BoundingSphere(const Vector3& centre, real radius);

		/**
		 * Creates a bounding sphere to enclose the two given bounding
		 * spheres.
		 */
		BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);

		/**
		 * Checks if the bounding sphere overlaps with the other given
		 * bounding sphere.
		 */
		bool overlaps(const BoundingSphere* other) const;

		/**
		 * Reports how much this bounding sphere would have to grow
		 * by to incorporate the given bounding sphere. Note that this
		 * calculation returns a value not in any particular units (i.e.
		 * its not a volume growth). In fact the best implementation
		 * takes into account the growth in surface area (after the
		 * Goldsmith-Salmon algorithm for tree construction).
		 */
		real getGrowth(const BoundingSphere& other) const;

		/**
		 * Returns the volume of this bounding volume. This is used
		 * to calculate how to recurse into the bounding volume tree.
		 * For a bounding sphere it is a simple calculation.
		 */
		real getSize() const
		{
			return ((real)1.333333) * R_PI * radius * radius * radius;
		}
	};
}