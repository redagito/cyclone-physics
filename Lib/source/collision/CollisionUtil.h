#pragma once

#include "cyclone/Precision.h"
#include "cyclone/collision/CollisionBox.h"

namespace cyclone
{
	class CollisionBox;
	class Vector3;

	real transformToAxis(
		const CollisionBox& box,
		const Vector3& axis
	);
}
