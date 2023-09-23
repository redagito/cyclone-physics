#pragma once

#include <cyclone/Cyclone.h>

/**
 * Fireworks are particles, with additional data for rendering and
 * evolution.
 */
class Firework : public cyclone::Particle
{
public:
	/** Fireworks have an integer type, used for firework rules. */
	unsigned type = 0;

	/**
	 * The age of a firework determines when it detonates. Age gradually
	 * decreases, when it passes zero the firework delivers its payload.
	 * Think of age as fuse-left.
	 */
	double age = 0.0;

	/**
	 * Updates the firework by the given duration of time. Returns true
	 * if the firework has reached the end of its life and needs to be
	 * removed.
	 */
	bool update(double duration);
};