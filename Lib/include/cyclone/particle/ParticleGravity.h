#pragma once

#include "cyclone/particle/ParticleForceGenerator.h"
#include "cyclone/Vector3.h"

namespace cyclone
{
    /**
     * A force generator that applies a gravitational force. One instance
     * can be used for multiple particles.
     */
    class ParticleGravity : public ParticleForceGenerator
    {
        /** Holds the acceleration due to gravity. */
        Vector3 gravity;

    public:

        /** Creates the generator with the given acceleration. */
        ParticleGravity(const Vector3& gravity);

        /** Applies the gravitational force to the given particle. */
        virtual void updateForce(Particle* particle, real duration);
    };

}