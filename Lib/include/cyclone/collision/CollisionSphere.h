#pragma once

#include "cyclone/collision/CollisionPrimitive.h"
#include "cyclone/Precision.h"

namespace cyclone
{
	/**
	 * Represents a rigid body that can be treated as a sphere
	 * for collision detection.
	 */
	class CollisionSphere : public CollisionPrimitive
	{
	public:
		/**
		 * The radius of the sphere.
		 */
		real radius = 0.f;
	};
}