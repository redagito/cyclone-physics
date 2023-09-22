#pragma once

#include "cyclone/Vector3.h"
#include "cyclone/Precision.h"

namespace cyclone
{
	/**
	 * The plane is not a primitive: it doesn't represent another
	 * rigid body. It is used for contacts with the immovable
	 * world geometry.
	 */
	class CollisionPlane
	{
	public:
		/**
		 * The plane normal
		 */
		Vector3 direction;

		/**
		 * The distance of the plane from the origin.
		 */
		real offset = 0.f;
	};
}