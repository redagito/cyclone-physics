#pragma once

#include <cyclone/Cyclone.h>

/**
 * A force generator for proximal attraction.
 */
class BlobForceGenerator : public cyclone::ParticleForceGenerator
{
public:
	/**
	* Holds a pointer to the particles we might be attracting.
	*/
	cyclone::Particle* particles = nullptr;

	/**
	 * The maximum force used to push the particles apart.
	 */
	double maxReplusion = 0.f;

	/**
	 * The maximum force used to pull particles together.
	 */
	double maxAttraction = 0.f;

	/**
	 * The separation between particles where there is no force.
	 */
	double minNaturalDistance = 0.0;
	double maxNaturalDistance = 0.0;

	/**
	 * The force with which to float the head particle, if it is
	 * joined to others.
	 */
	double floatHead = 0.f;

	/**
	 * The maximum number of particles in the blob before the head
	 * is floated at maximum force.
	 */
	unsigned maxFloat = 0.f;

	/**
	 * The separation between particles after which they 'break' apart and
	 * there is no force.
	 */
	double maxDistance = 0.f;

	virtual void updateForce(
		cyclone::Particle* particle,
		double duration
	);
};
