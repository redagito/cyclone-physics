#pragma once

#include "cyclone/force/ParticleForceGenerator.h"

namespace cyclone
{

    /**
     * A force generator that applies a drag force. One instance
     * can be used for multiple particles.
     */
    class ParticleDrag : public ParticleForceGenerator
    {
        /** Holds the velocity drag coeffificent. */
        double k1;

        /** Holds the velocity squared drag coeffificent. */
        double k2;

    public:

        /** Creates the generator with the given coefficients. */
        ParticleDrag(double k1, double k2);

        /** Applies the drag force to the given particle. */
        virtual void updateForce(Particle* particle, double duration);
    };
}