#pragma once

#include "cyclone/collision/CollisionPrimitive.h"

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
		double radius = 0.f;
	};
}