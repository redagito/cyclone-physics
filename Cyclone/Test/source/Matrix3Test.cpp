#include <catch2/catch_test_macros.hpp>

#include <cyclone/Matrix3.h>

TEST_CASE("Matrix3_Ctor_DefaultZero", "[matrix3]")
{
	cyclone::Matrix3 mat3;
	for (auto d : mat3.data)
	{
		REQUIRE(d == 0.0);
	}
}