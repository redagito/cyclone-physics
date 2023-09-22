#include "cyclone/collision/IntersectionTests.h"
#include "cyclone/collision/CollisionSphere.h"
#include "cyclone/collision/CollisionPlane.h"
#include "cyclone/collision/CollisionBox.h"
#include "cyclone/Precision.h"
#include "cyclone/Vector3.h"
#include "collision/CollisionUtil.h"

using namespace cyclone;

bool IntersectionTests::sphereAndHalfSpace(
	const CollisionSphere& sphere,
	const CollisionPlane& plane)
{
	// Find the distance from the origin
	real ballDistance =
		plane.direction *
		sphere.getAxis(3) -
		sphere.radius;

	// Check for the intersection
	return ballDistance <= plane.offset;
}

bool IntersectionTests::sphereAndSphere(
	const CollisionSphere& one,
	const CollisionSphere& two)
{
	// Find the vector between the objects
	Vector3 midline = one.getAxis(3) - two.getAxis(3);

	// See if it is large enough.
	return midline.squareMagnitude() <
		(one.radius + two.radius) * (one.radius + two.radius);
}

/**
 * This function checks if the two boxes overlap
 * along the given axis. The final parameter toCentre
 * is used to pass in the vector between the boxes centre
 * points, to avoid having to recalculate it each time.
 */
static inline bool overlapOnAxis(
	const CollisionBox& one,
	const CollisionBox& two,
	const Vector3& axis,
	const Vector3& toCentre
)
{
	// Project the half-size of one onto axis
	real oneProject = transformToAxis(one, axis);
	real twoProject = transformToAxis(two, axis);

	// Project this onto the axis
	real distance = real_abs(toCentre * axis);

	// Check for overlap
	return (distance < oneProject + twoProject);
}

// This preprocessor definition is only used as a convenience
// in the boxAndBox intersection  method.
#define TEST_OVERLAP(axis) overlapOnAxis(one, two, (axis), toCentre)

bool IntersectionTests::boxAndBox(
	const CollisionBox& one,
	const CollisionBox& two
)
{
	// Find the vector between the two centres
	Vector3 toCentre = two.getAxis(3) - one.getAxis(3);

	return (
		// Check on box one's axes first
		TEST_OVERLAP(one.getAxis(0)) &&
		TEST_OVERLAP(one.getAxis(1)) &&
		TEST_OVERLAP(one.getAxis(2)) &&

		// And on two's
		TEST_OVERLAP(two.getAxis(0)) &&
		TEST_OVERLAP(two.getAxis(1)) &&
		TEST_OVERLAP(two.getAxis(2)) &&

		// Now on the cross products
		TEST_OVERLAP(one.getAxis(0) % two.getAxis(0)) &&
		TEST_OVERLAP(one.getAxis(0) % two.getAxis(1)) &&
		TEST_OVERLAP(one.getAxis(0) % two.getAxis(2)) &&
		TEST_OVERLAP(one.getAxis(1) % two.getAxis(0)) &&
		TEST_OVERLAP(one.getAxis(1) % two.getAxis(1)) &&
		TEST_OVERLAP(one.getAxis(1) % two.getAxis(2)) &&
		TEST_OVERLAP(one.getAxis(2) % two.getAxis(0)) &&
		TEST_OVERLAP(one.getAxis(2) % two.getAxis(1)) &&
		TEST_OVERLAP(one.getAxis(2) % two.getAxis(2))
		);
}
#undef TEST_OVERLAP

bool IntersectionTests::boxAndHalfSpace(
	const CollisionBox& box,
	const CollisionPlane& plane
)
{
	// Work out the projected radius of the box onto the plane direction
	real projectedRadius = transformToAxis(box, plane.direction);

	// Work out how far the box is from the origin
	real boxDistance =
		plane.direction *
		box.getAxis(3) -
		projectedRadius;

	// Check for the intersection
	return boxDistance <= plane.offset;
}