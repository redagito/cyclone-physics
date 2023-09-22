#pragma once

#include "cyclone/Vector3.h"
#include "cyclone/collision/CollisionPrimitive.h"

namespace cyclone
{
	/**
	 * Represents a rigid body that can be treated as an aligned bounding
	 * box for collision detection.
	 */
	class CollisionBox : public CollisionPrimitive
	{
	public:
		/**
		 * Holds the half-sizes of the box along each of its local axes.
		 */
		Vector3 halfSize;
	};
}