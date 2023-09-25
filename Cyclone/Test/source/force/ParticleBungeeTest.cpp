#include <catch2/catch_test_macros.hpp>

#include <cyclone/force/ParticleBungee.h>

TEST_CASE("ParticleBungee", "[particlebungee]")
{
	cyclone::ParticleBungee pb{ nullptr, 0.0, 0.0 };
	REQUIRE(true);
}