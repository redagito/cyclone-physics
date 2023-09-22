#include "collision/CollisionUtil.h"
#include "cyclone/collision/CollisionBox.h"
#include "cyclone/Vector3.h"

namespace cyclone
{
	real transformToAxis(
		const CollisionBox& box,
		const Vector3& axis
	)
	{
		return
			box.halfSize.x * real_abs(axis * box.getAxis(0)) +
			box.halfSize.y * real_abs(axis * box.getAxis(1)) +
			box.halfSize.z * real_abs(axis * box.getAxis(2));
	}
}