#pragma once

#include <cyclone/Cyclone.h>

/**
 * Platforms are two dimensional: lines on which the
 * particles can rest. Platforms are also contact generators for the physics.
 */
class Platform : public cyclone::ParticleContactGenerator
{
public:
	cyclone::Vector3 start;
	cyclone::Vector3 end;

	/**
	 * Holds a pointer to the particles we're checking for collisions with.
	 */
	cyclone::Particle* particles = nullptr;

	virtual unsigned addContact(
		cyclone::ParticleContact* contact,
		unsigned limit
	) const;
};