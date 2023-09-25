#pragma once

#include <cyclone/Cyclone.h>

class Box : public cyclone::CollisionBox
{
public:
	Box();
	~Box();

	/** Draws the box, excluding its shadow. */
	void render();

	/** Sets the box to a specific location. */
	void setState(double z);
};