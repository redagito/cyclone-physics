#pragma once

#include "cyclone/force/ParticleForceGenerator.h"

namespace cyclone
{


    /**
     * A force generator that applies a spring force only
     * when extended.
     */
    class ParticleBungee : public ParticleForceGenerator
    {
        /** The particle at the other end of the spring. */
        Particle* other = nullptr;

        /** Holds the sprint constant. */
        double springConstant = 0.0;

        /**
         * Holds the length of the bungee at the point it begins to
         * generator a force.
         */
        double restLength = 0.0;

    public:

        /** Creates a new bungee with the given parameters. */
        ParticleBungee(Particle* other,
            double springConstant, double restLength);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle* particle, double duration);
    };
}