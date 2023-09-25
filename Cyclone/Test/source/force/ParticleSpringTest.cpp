#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/ParticleSpring.h>

TEST_CASE("ParticleSpring", "[particlespring]")
{
	cyclone::ParticleSpring ps{ nullptr, 0.0, 0.0 };
	REQUIRE(true);
}