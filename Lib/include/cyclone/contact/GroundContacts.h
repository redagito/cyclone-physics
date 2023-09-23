#pragma once

#include "cyclone/contact/ParticleContactGenerator.h"
#include "cyclone/Particles.h"

namespace cyclone
{
	/**
	 * A contact generator that takes an STL vector of particle pointers and
	 * collides them against the ground.
	 */
	class GroundContacts : public ParticleContactGenerator
	{
		cyclone::Particles* particles = nullptr;

	public:
		void init(cyclone::Particles* particles);

		virtual unsigned addContact(cyclone::ParticleContact* contact,
			unsigned limit) const;
	};
}