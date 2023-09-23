#include "collision/CollisionUtil.h"
#include "cyclone/collision/CollisionBox.h"
#include "cyclone/Vector3.h"

namespace cyclone
{
	double transformToAxis(
		const CollisionBox& box,
		const Vector3& axis
	)
	{
		return
			box.halfSize.x * std::abs(axis * box.getAxis(0)) +
			box.halfSize.y * std::abs(axis * box.getAxis(1)) +
			box.halfSize.z * std::abs(axis * box.getAxis(2));
	}
}