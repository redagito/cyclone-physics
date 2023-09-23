#pragma once

#include "cyclone/force/ParticleForceGenerator.h"

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
		double springConstant = 0.f;

		/** Holds the rest length of the spring. */
		double restLength = 0.f;

	public:
		ParticleAnchoredSpring() = default;

		/** Creates a new spring with the given parameters. */
		ParticleAnchoredSpring(Vector3* anchor,
			double springConstant,
			double restLength);

		/** Retrieve the anchor point. */
		const Vector3* getAnchor() const { return anchor; }

		/** Set the spring's properties. */
		void init(Vector3* anchor,
			double springConstant,
			double restLength);

		/** Applies the spring force to the given particle. */
		virtual void updateForce(Particle* particle, double duration);
	};
}
