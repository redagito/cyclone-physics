#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/AeroControl.h>

TEST_CASE("AeroControl", "[aerocontrol]")
{
	cyclone::AeroControl ac{ cyclone::Matrix3{}, cyclone::Matrix3{}, cyclone::Matrix3{}, cyclone::Vector3{}, nullptr };
	REQUIRE(true);
}