#pragma once

#include "cyclone/force/ParticleForceGenerator.h"

namespace cyclone
{
    class Vector3;

    /**
     * A force generator that fakes a stiff spring force, and where
     * one end is attached to a fixed point in space.
     */
    class ParticleFakeSpring : public ParticleForceGenerator
    {
        /** The location of the anchored end of the spring. */
        Vector3* anchor = nullptr;

        /** Holds the sprint constant. */
        double springConstant = 0.0;

        /** Holds the damping on the oscillation of the spring. */
        double damping = 0.0;

    public:

        /** Creates a new spring with the given parameters. */
        ParticleFakeSpring(Vector3* anchor, double springConstant,
            double damping);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle* particle, double duration);
    };
}