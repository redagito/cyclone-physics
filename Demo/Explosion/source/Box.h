#pragma once

#include <cyclone/Cyclone.h>

class Box : public cyclone::CollisionBox
{
public:
	bool isOverlapping = false;

	Box();

	~Box();

	/** Draws the box, excluding its shadow. */
	void render();

	/** Draws the ground plane shadow for the box. */
	void renderShadow();

	/** Sets the box to a specific location. */
	void setState(const cyclone::Vector3& position,
		const cyclone::Quaternion& orientation,
		const cyclone::Vector3& extents,
		const cyclone::Vector3& velocity);

	/** Positions the box at a random location. */
	void random(cyclone::Random* random);
};