#pragma once

#include "cyclone/particle/ParticleForceGenerator.h"

namespace cyclone
{


    /**
     * A force generator that applies a spring force only
     * when extended.
     */
    class ParticleBungee : public ParticleForceGenerator
    {
        /** The particle at the other end of the spring. */
        Particle* other;

        /** Holds the sprint constant. */
        real springConstant;

        /**
         * Holds the length of the bungee at the point it begins to
         * generator a force.
         */
        real restLength;

    public:

        /** Creates a new bungee with the given parameters. */
        ParticleBungee(Particle* other,
            real springConstant, real restLength);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle* particle, real duration);
    };
}