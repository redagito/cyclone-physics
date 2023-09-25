#pragma once

#include "cyclone/collision/CollisionBox.h"

namespace cyclone
{
	class CollisionBox;
	class Vector3;

	double transformToAxis(
		const CollisionBox& box,
		const Vector3& axis
	);
}
