#pragma once

#include "cyclone/particle/ParticleForceGenerator.h"

namespace cyclone
{
	class Vector3;

	/**
	 * A force generator that applies a Spring force, where
	 * one end is attached to a fixed point in space.
	 */
	class ParticleAnchoredSpring : public ParticleForceGenerator
	{
	protected:
		/** The location of the anchored end of the spring. */
		Vector3* anchor = nullptr;

		/** Holds the sprint constant. */
		real springConstant = 0.f;

		/** Holds the rest length of the spring. */
		real restLength = 0.f;

	public:
		ParticleAnchoredSpring() = default;

		/** Creates a new spring with the given parameters. */
		ParticleAnchoredSpring(Vector3* anchor,
			real springConstant,
			real restLength);

		/** Retrieve the anchor point. */
		const Vector3* getAnchor() const { return anchor; }

		/** Set the spring's properties. */
		void init(Vector3* anchor,
			real springConstant,
			real restLength);

		/** Applies the spring force to the given particle. */
		virtual void updateForce(Particle* particle, real duration);
	};
}
