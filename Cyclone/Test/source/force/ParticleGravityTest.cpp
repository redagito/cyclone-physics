#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/ParticleGravity.h>

TEST_CASE("ParticleGravity", "[particlegravity]")
{
	cyclone::ParticleGravity pg{ cyclone::Vector3{} };
	REQUIRE(true);
}