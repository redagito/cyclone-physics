#pragma once

#include "cyclone/Precision.h"
#include "cyclone/Vector3.h"

namespace cyclone
{
	class Particle;

	/**
	 * A Contact represents two objects in contact (in this case
	 * ParticleContact representing two Particles). Resolving a
	 * contact removes their interpenetration, and applies sufficient
	 * impulse to keep them apart. Colliding bodies may also rebound.
	 *
	 * The contact has no callable functions, it just holds the
	 * contact details. To resolve a set of contacts, use the particle
	 * contact resolver class.
	 */
	class ParticleContact
	{
		// ... Other ParticleContact code as before ...


		/**
		 * The contact resolver object needs access into the contacts to
		 * set and effect the contact.
		 */
		friend class ParticleContactResolver;


	public:
		/**
		 * Holds the particles that are involved in the contact. The
		 * second of these can be NULL, for contacts with the scenery.
		 */
		Particle* particle[2];

		/**
		 * Holds the normal restitution coefficient at the contact.
		 */
		real restitution = 0.f;

		/**
		 * Holds the direction of the contact in world coordinates.
		 */
		Vector3 contactNormal;

		/**
		 * Holds the depth of penetration at the contact.
		 */
		real penetration;

		/**
		 * Holds the amount each particle is moved by during interpenetration
		 * resolution.
		 */
		Vector3 particleMovement[2];

	protected:
		/**
		 * Resolves this contact, for both velocity and interpenetration.
		 */
		void resolve(real duration);

		/**
		 * Calculates the separating velocity at this contact.
		 */
		real calculateSeparatingVelocity() const;

	private:
		/**
		 * Handles the impulse calculations for this collision.
		 */
		void resolveVelocity(real duration);

		/**
		 * Handles the interpenetration resolution for this contact.
		 */
		void resolveInterpenetration(real duration);

	};
}