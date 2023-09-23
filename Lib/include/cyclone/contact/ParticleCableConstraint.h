#pragma once

#include "cyclone/contact/ParticleConstraint.h"

namespace cyclone
{
	class ParticleContact;

	/**
	* Cables link a particle to an anchor point, generating a contact if they
	* stray too far apart.
	*/
	class ParticleCableConstraint : public ParticleConstraint
	{
	public:
		/**
		* Holds the maximum length of the cable.
		*/
		double maxLength = 0.f;

		/**
		* Holds the restitution (bounciness) of the cable.
		*/
		double restitution = 0.f;

	public:
		/**
		* Fills the given contact structure with the contact needed
		* to keep the cable from over-extending.
		*/
		virtual unsigned addContact(ParticleContact* contact,
			unsigned limit) const;
	};
}