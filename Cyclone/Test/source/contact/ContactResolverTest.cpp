#include <catch2/catch_test_macros.hpp>

#include <cyclone/contact/ContactResolver.h>

TEST_CASE("ContactResolver", "[contactresolver]")
{
	cyclone::ContactResolver resolver{ 5 };
	REQUIRE(true);
}