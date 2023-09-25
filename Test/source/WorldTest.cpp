#include <catch2/catch_test_macros.hpp>

#include <cyclone/World.h>

TEST_CASE("World", "[world]")
{
	cyclone::World world{ 256 };
	REQUIRE(true);
}