#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/Buoyancy.h>

TEST_CASE("Buoyancy", "[buoyancy]")
{
	cyclone::Buoyancy b{ cyclone::Vector3{}, 0.0, 0.0, 0.0 };
	REQUIRE(true);
}