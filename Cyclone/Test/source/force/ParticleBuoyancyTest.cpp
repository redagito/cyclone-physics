#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/ParticleBuoyancy.h>

TEST_CASE("ParticleBuoyancy", "[particlebuoyancy]")
{
	cyclone::ParticleBuoyancy pb{ 0.0, 0.0, 0.0 };
	REQUIRE(true);
}