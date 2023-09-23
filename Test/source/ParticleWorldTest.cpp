#include <catch2/catch_all.hpp>

#include <cyclone/ParticleWorld.h>

TEST_CASE("ParticleWorld", "[particleworld]")
{
	cyclone::ParticleWorld world{ 100 };
	REQUIRE(true);
}