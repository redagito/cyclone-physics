#pragma once

#include "cyclone/force/ParticleForceGenerator.h"

namespace cyclone
{

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
        double maxDepth = 0.0;

        /**
         * The volume of the object.
         */
        double volume = 0.0;

        /**
         * The height of the water plane above y=0. The plane will be
         * parrallel to the XZ plane.
         */
        double waterHeight = 0.0;

        /**
         * The density of the liquid. Pure water has a density of
         * 1000kg per cubic meter.
         */
        double liquidDensity = 0.0;

    public:

        /** Creates a new buoyancy force with the given parameters. */
        ParticleBuoyancy(double maxDepth, double volume, double waterHeight,
            double liquidDensity = 1000.0f);

        /** Applies the buoyancy force to the given particle. */
        virtual void updateForce(Particle* particle, double duration);
    };
}