#pragma once

#include <cyclone/Cyclone.h>

class Ball : public cyclone::CollisionSphere
{
public:
	Ball();

	~Ball();

	/** Draws the box, excluding its shadow. */
	void render();

	/** Draws the ground plane shadow for the box. */
	void renderShadow();

	/** Sets the box to a specific location. */
	void setState(cyclone::Vector3 position,
		cyclone::Quaternion orientation,
		double radius,
		cyclone::Vector3 velocity);

	/** Positions the box at a random location. */
	void random(cyclone::Random* random);
};