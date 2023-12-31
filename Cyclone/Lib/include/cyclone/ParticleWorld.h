#pragma once

/*
 * Interface file for the particle / mass aggregate world structure.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

 /**
  * @file
  *
  * This file contains the definitions for a structure to hold any number o
  * particle masses, and their connections.
  */

#include "cyclone/force/ParticleForceRegistry.h"
#include "cyclone/contact/ParticleContactGenerator.h"
#include "cyclone/contact/ParticleContactResolver.h"
#include "cyclone/Particles.h"

namespace cyclone {

	/**
	 * Keeps track of a set of particles, and provides the means to
	 * update them all.
	 */
	class ParticleWorld
	{
	public:
		typedef std::vector<ParticleContactGenerator*> ContactGenerators;

	protected:
		/**
		 * Holds the particles
		 */
		Particles particles;

		/**
		 * True if the world should calculate the number of iterations
		 * to give the contact resolver at each frame.
		 */
		bool calculateIterations = false;

		/**
		 * Holds the force generators for the particles in this world.
		 */
		ParticleForceRegistry registry;

		/**
		 * Holds the resolver for contacts.
		 */
		ParticleContactResolver resolver;

		/**
		 * Contact generators.
		 */
		ContactGenerators contactGenerators;

		/**
		 * Holds the list of contacts.
		 */
		ParticleContact* contacts = nullptr;

		/**
		 * Holds the maximum number of contacts allowed (i.e. the
		 * size of the contacts array).
		 */
		unsigned maxContacts = 0;

	public:

		/**
		 * Creates a new particle simulator that can handle up to the
		 * given number of contacts per frame. You can also optionally
		 * give a number of contact-resolution iterations to use. If you
		 * don't give a number of iterations, then twice the number of
		 * contacts will be used.
		 */
		ParticleWorld(unsigned maxContacts, unsigned iterations = 0);

		/**
		 * Deletes the simulator.
		 */
		~ParticleWorld();

		/**
		 * Calls each of the registered contact generators to report
		 * their contacts. Returns the number of generated contacts.
		 */
		unsigned generateContacts();

		/**
		 * Integrates all the particles in this world forward in time
		 * by the given duration.
		 */
		void integrate(double duration);

		/**
		 * Processes all the physics for the particle world.
		 */
		void runPhysics(double duration);

		/**
		 * Initializes the world for a simulation frame. This clears
		 * the force accumulators for particles in the world. After
		 * calling this, the particles can have their forces for this
		 * frame added.
		 */
		void startFrame();

		/**
		 *  Returns the list of particles.
		 */
		Particles& getParticles();

		/**
		 * Returns the list of contact generators.
		 */
		ContactGenerators& getContactGenerators();

		/**
		 * Returns the force registry.
		 */
		ParticleForceRegistry& getForceRegistry();

		/**
		* Registers the force generator to affect ALL particles in the world
		*/
		void registerGlobalForceGenerator(ParticleForceGenerator* generator);

		// Clears the world
		void clear();
	};
}