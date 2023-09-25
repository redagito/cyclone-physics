#include <catch2/catch_test_macros.hpp>

#include <cyclone/contact/ParticleContactResolver.h>

TEST_CASE("ParticleContactResolver", "[particlecontactresolver]")
{
	cyclone::ParticleContactResolver pcr{ 100 };
	REQUIRE(true);
}