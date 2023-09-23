#include <catch2/catch_test_macros.hpp>

#include <cyclone/collision/CollisionDetector.h>
#include <cyclone/collision/CollisionData.h>
#include <cyclone/contact/Contact.h>
#include <cyclone/collision/CollisionBox.h>
#include <cyclone/collision/CollisionSphere.h>
#include <cyclone/RigidBody.h>

TEST_CASE("CollisionDetector_BoxAndSphere_NoCollision", "[collisiondetector]")
{
	cyclone::RigidBody b1;
	cyclone::RigidBody b2;

	cyclone::Contact contacts[10];
	cyclone::CollisionData data;
	data.contactArray = contacts;
	data.reset(10);

	// Box at origin with 0.5 half size, unit size box
	cyclone::CollisionBox box;
	box.body = &b1;
	box.body->setPosition(0.0, 0.0, -0.5);
	box.halfSize = cyclone::Vector3(0.5, 0.5, 0.5);

	cyclone::CollisionSphere sphere;
	sphere.body = &b2;
	sphere.body->setPosition(0.0, 0.0, 0.6);
	sphere.radius = 0.5;

	REQUIRE(cyclone::CollisionDetector::boxAndSphere(box, sphere, &data) == 0);
	REQUIRE(data.contactCount == 0);
}