#pragma once

#include "cyclone/contact/ParticleLink.h"

namespace cyclone
{

	/**
	 * Rods link a pair of particles, generating a contact if they
	 * stray too far apart or too close.
	 */
	class ParticleRod : public ParticleLink
	{
	public:
		/**
		 * Holds the length of the rod.
		 */
		real length;

	public:
		/**
		 * Fills the given contact structure with the contact needed
		 * to keep the rod from extending or compressing.
		 */
		virtual unsigned addContact(ParticleContact* contact,
			unsigned limit) const;
	};
}