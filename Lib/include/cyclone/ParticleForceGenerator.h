#pragma once

namespace cyclone 
{
    /**
     * A force generator can be asked to add a force to one or more
     * particles.
     */
    class ParticleForceGenerator
    {
    public:

        /**
         * Overload this in implementations of the interface to calculate
         * and update the force applied to the given particle.
         */
        virtual void updateForce(Particle* particle, real duration) = 0;
    };
}