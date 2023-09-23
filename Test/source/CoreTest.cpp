#include <catch2/catch_all.hpp>

#include <cyclone/Core.h>

TEST_CASE("Core_DefaultSleepEpsilon_GreaterZero", "[core]")
{
	REQUIRE(cyclone::getSleepEpsilon() > 0.f);
}

TEST_CASE("Core_GetSetSleepEpsilon", "[core]")
{
	cyclone::setSleepEpsilon(0.1f);
	REQUIRE(cyclone::getSleepEpsilon() == 0.1f);
}