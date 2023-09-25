#pragma once

#include <cyclone/Cyclone.h>

#include "ShotType.h"

/**
* Holds a single ammunition round record.
*/
class AmmoRound
{
public:
	cyclone::Particle particle;
	ShotType type = ShotType::PISTOL;
	unsigned startTime = 0;

	/** Draws the round. */
	void render() const;
};