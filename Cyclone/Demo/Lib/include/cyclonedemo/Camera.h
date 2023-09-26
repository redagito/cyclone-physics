#pragma once

#include <cyclone/Cyclone.h>

class Camera
{
public:
	cyclone::Vector3 position;
	cyclone::Vector3 lookAt = cyclone::Vector3{0.0, 0.0, 0.0};
	cyclone::Vector3 up = cyclone::Vector3::UP;
};