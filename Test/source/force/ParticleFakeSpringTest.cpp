#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/ParticleFakeSpring.h>

TEST_CASE("ParticleFakeSpring", "[particlefakespring]")
{
	cyclone::ParticleFakeSpring pfs{ nullptr, 0.0, 0.0 };
	REQUIRE(true);
}