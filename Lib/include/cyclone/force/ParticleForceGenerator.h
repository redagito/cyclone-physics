#pragma once

namespace cyclone
{
	class Particle;

	/**
	 * A force generator can be asked to add a force to one or more
	 * particles.
	 */
	class ParticleForceGenerator
	{
	public:
		virtual ~ParticleForceGenerator() = default;

		/**
		 * Overload this in implementations of the interface to calculate
		 * and update the force applied to the given particle.
		 */
		virtual void updateForce(Particle* particle, double duration) = 0;
	};
}