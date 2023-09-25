#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/Gravity.h>

TEST_CASE("Gravity", "[gravity]")
{
	cyclone::Gravity g{ cyclone::Vector3{} };
	REQUIRE(true);
}