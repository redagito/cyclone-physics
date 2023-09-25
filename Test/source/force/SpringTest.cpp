#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/Spring.h>

TEST_CASE("Spring", "[spring]")
{
	cyclone::Spring ps{ cyclone::Vector3{}, nullptr, cyclone::Vector3{}, 0.0, 0.0 };
	REQUIRE(true);
}