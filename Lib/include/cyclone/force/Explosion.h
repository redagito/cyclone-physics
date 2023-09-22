#pragma once

#include "cyclone/force/ForceGenerator.h"
#include "cyclone/force/ParticleForceGenerator.h"
#include "cyclone/Vector3.h"

namespace cyclone
{

	/**
	 * A force generator showing a three component explosion effect.
	 * This force generator is intended to represent a single
	 * explosion effect for multiple rigid bodies. The force generator
	 * can also act as a particle force generator.
	 */
	class Explosion : public ForceGenerator,
		public ParticleForceGenerator
	{
		/**
		 * Tracks how long the explosion has been in operation, used
		 * for time-sensitive effects.
		 */
		real timePassed = 0.f;

	public:
		// Properties of the explosion, these are public because
		// there are so many and providing a suitable constructor
		// would be cumbersome:

		/**
		 * The location of the detonation of the weapon.
		 */
		Vector3 detonation;

		// ... Other Explosion code as before ...


		/**
		 * The radius up to which objects implode in the first stage
		 * of the explosion.
		 */
		real implosionMaxRadius = 0.f;

		/**
		 * The radius within which objects don't feel the implosion
		 * force. Objects near to the detonation aren't sucked in by
		 * the air implosion.
		 */
		real implosionMinRadius = 0.f;

		/**
		 * The length of time that objects spend imploding before the
		 * concussion phase kicks in.
		 */
		real implosionDuration = 0.f;

		/**
		 * The maximal force that the implosion can apply. This should
		 * be relatively small to avoid the implosion pulling objects
		 * through the detonation point and out the other side before
		 * the concussion wave kicks in.
		 */
		real implosionForce = 0.f;

		/**
		 * The speed that the shock wave is traveling, this is related
		 * to the thickness below in the relationship:
		 *
		 * thickness >= speed * minimum frame duration
		 */
		real shockwaveSpeed = 0.f;

		/**
		 * The shock wave applies its force over a range of distances,
		 * this controls how thick. Faster waves require larger
		 * thicknesses.
		 */
		real shockwaveThickness = 0.f;

		/**
		 * This is the force that is applied at the very centre of the
		 * concussion wave on an object that is stationary. Objects
		 * that are in front or behind of the wavefront, or that are
		 * already moving outwards, get proportionally less
		 * force. Objects moving in towards the centre get
		 * proportionally more force.
		 */
		real peakConcussionForce = 0.f;

		/**
		 * The length of time that the concussion wave is active.
		 * As the wave nears this, the forces it applies reduces.
		 */
		real concussionDuration = 0.f;

		/**
		 * This is the peak force for stationary objects in
		 * the centre of the convection chimney. Force calculations
		 * for this value are the same as for peakConcussionForce.
		 */
		real peakConvectionForce = 0.f;

		/**
		 * The radius of the chimney cylinder in the xz plane.
		 */
		real chimneyRadius = 0.f;

		/**
		 * The maximum height of the chimney.
		 */
		real chimneyHeight = 0.f;

		/**
		 * The length of time the convection chimney is active. Typically
		 * this is the longest effect to be in operation, as the heat
		 * from the explosion outlives the shock wave and implosion
		 * itself.
		 */
		real convectionDuration = 0.f;

	public:
		/**
		 * Creates a new explosion with sensible default values.
		 */
		Explosion();

		/**
		 * Calculates and applies the force that the explosion
		 * has on the given rigid body.
		 */
		virtual void updateForce(RigidBody* body, real duration);

		/**
		 * Calculates and applies the force that the explosion has
		 * on the given particle.
		 */
		virtual void updateForce(Particle* particle, real duration);

	};
}