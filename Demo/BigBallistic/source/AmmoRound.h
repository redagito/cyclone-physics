#pragma once

#include <cyclone/Cyclone.h>
#include "ShotType.h"

class AmmoRound : public cyclone::CollisionSphere
{
public:
	ShotType type = ShotType::PISTOL;
	unsigned startTime = 0;

	AmmoRound();

	~AmmoRound();

	/** Draws the box, excluding its shadow. */
	void render();

	/** Sets the box to a specific location. */
	void setState(ShotType shotType);
};