#pragma once

/*
 * Interface file for the force generators.
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
 * This file contains the interface and sample force generators.
 */

#include "core.h"
#include "cyclone/particle/Particle.h"
#include "cyclone/particle/ParticleForceGenerator.h"
#include <vector>

namespace cyclone {





    /**
     * A force generator that fakes a stiff spring force, and where
     * one end is attached to a fixed point in space.
     */
    class ParticleFakeSpring : public ParticleForceGenerator
    {
        /** The location of the anchored end of the spring. */
        Vector3 *anchor;

        /** Holds the sprint constant. */
        real springConstant;

        /** Holds the damping on the oscillation of the spring. */
        real damping;

    public:

        /** Creates a new spring with the given parameters. */
        ParticleFakeSpring(Vector3 *anchor, real springConstant,
            real damping);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
     * A force generator that applies a Spring force.
     */
    class ParticleSpring : public ParticleForceGenerator
    {
        /** The particle at the other end of the spring. */
        Particle *other;

        /** Holds the sprint constant. */
        real springConstant;

        /** Holds the rest length of the spring. */
        real restLength;

    public:

        /** Creates a new spring with the given parameters. */
        ParticleSpring(Particle *other,
            real springConstant, real restLength);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
     * A force generator that applies a spring force only
     * when extended.
     */
    class ParticleBungee : public ParticleForceGenerator
    {
        /** The particle at the other end of the spring. */
        Particle *other;

        /** Holds the sprint constant. */
        real springConstant;

        /**
         * Holds the length of the bungee at the point it begins to
         * generator a force.
         */
        real restLength;

    public:

        /** Creates a new bungee with the given parameters. */
        ParticleBungee(Particle *other,
            real springConstant, real restLength);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
     * A force generator that applies a buoyancy force for a plane of
     * liquid parrallel to XZ plane.
     */
    class ParticleBuoyancy : public ParticleForceGenerator
    {
        /**
         * The maximum submersion depth of the object before
         * it generates its maximum boyancy force.
         */
        real maxDepth;

        /**
         * The volume of the object.
         */
        real volume;

        /**
         * The height of the water plane above y=0. The plane will be
         * parrallel to the XZ plane.
         */
        real waterHeight;

        /**
         * The density of the liquid. Pure water has a density of
         * 1000kg per cubic meter.
         */
        real liquidDensity;

    public:

        /** Creates a new buoyancy force with the given parameters. */
        ParticleBuoyancy(real maxDepth, real volume, real waterHeight,
            real liquidDensity = 1000.0f);

        /** Applies the buoyancy force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
     * Holds all the force generators and the particles they apply to.
     */
    class ParticleForceRegistry
    {
    protected:

        /**
         * Keeps track of one force generator and the particle it
         * applies to.
         */
        struct ParticleForceRegistration
        {
            Particle *particle;
            ParticleForceGenerator *fg;
        };

        /**
         * Holds the list of registrations.
         */
        typedef std::vector<ParticleForceRegistration> Registry;
        Registry registrations;

    public:
        /**
         * Registers the given force generator to apply to the
         * given particle.
         */
        void add(Particle* particle, ParticleForceGenerator *fg);

        /**
         * Removes the given registered pair from the registry.
         * If the pair is not registered, this method will have
         * no effect.
         */
        void remove(Particle* particle, ParticleForceGenerator *fg);

        /**
         * Clears all registrations from the registry. This will
         * not delete the particles or the force generators
         * themselves, just the records of their connection.
         */
        void clear();

        /**
         * Calls all the force generators to update the forces of
         * their corresponding particles.
         */
        void updateForces(real duration);
    };
}