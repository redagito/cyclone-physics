#pragma once

#include "cyclone/force/ParticleForceGenerator.h"

namespace cyclone
{
	/**
	 * A force generator that applies a Spring force.
	 */
	class ParticleSpring : public ParticleForceGenerator
	{
	private:
		/** The particle at the other end of the spring. */
		Particle* other = nullptr;

		/** Holds the sprint constant. */
		double springConstant = 0.0;

		/** Holds the rest length of the spring. */
		double restLength = 0.0;

	public:

		/** Creates a new spring with the given parameters. */
		ParticleSpring(Particle* other,
			double springConstant, double restLength);

		/** Applies the spring force to the given particle. */
		virtual void updateForce(Particle* particle, double duration);
	};
}