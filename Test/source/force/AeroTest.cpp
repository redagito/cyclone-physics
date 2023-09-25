#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/Aero.h>

TEST_CASE("Aero", "[aero]")
{
	cyclone::Aero{ cyclone::Matrix3{}, cyclone::Vector3{}, nullptr };
	REQUIRE(true);
}