#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/AngledAero.h>

TEST_CASE("AngledAero", "[angledaero]")
{
	cyclone::AngledAero aa{ cyclone::Matrix3{}, cyclone::Vector3{}, nullptr };
	REQUIRE(true);
}