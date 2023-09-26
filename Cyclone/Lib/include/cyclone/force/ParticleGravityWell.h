#pragma once

#include "cyclone/force/ParticleForceGenerator.h"
#include "cyclone/Vector3.h"

namespace cyclone
{
    /**
     * A force generator that applies a force towards a fixed point. One instance
     * can be used for multiple particles.
     */
    class ParticleGravityWell : public ParticleForceGenerator
    {
        /** Holds the acceleration due to gravity in [m/s] */
        double force = 0.0;
        // Radius in which no force is applied in [m]
        double deadZoneRadius = 1.0;
        // Position of the gravity well in world coordinates
        Vector3 position;

    public:

        /** Creates the generator with the given acceleration. */
        ParticleGravityWell(double force, const Vector3& position, float deadZoneRadius);

        /** Applies the gravitational force to the given particle. */
        virtual void updateForce(Particle* particle, double duration);
    };

}