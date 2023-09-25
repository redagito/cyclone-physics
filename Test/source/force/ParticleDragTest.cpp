#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/ParticleDrag.h>

TEST_CASE("ParticleDrag", "[particledrag]")
{
	cyclone::ParticleDrag pd{ 0.0, 0.0 };
	REQUIRE(true);
}