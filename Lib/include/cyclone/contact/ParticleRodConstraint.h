#pragma once

#include "cyclone/contact/ParticleConstraint.h"
#include "cyclone/Precision.h"

namespace cyclone
{

	/**
	* Rods link a particle to an anchor point, generating a contact if they
	* stray too far apart or too close.
	*/
	class ParticleRodConstraint : public ParticleConstraint
	{
	public:
		/**
		* Holds the length of the rod.
		*/
		real length = 0.f;

	public:
		/**
		* Fills the given contact structure with the contact needed
		* to keep the rod from extending or compressing.
		*/
		virtual unsigned addContact(ParticleContact* contact,
			unsigned limit) const;
	};
}