#pragma once

#include "cyclone/particle/ParticleAnchoredSpring.h"
#include "cyclone/Precision.h"

namespace cyclone
{
    class Particle;

    /**
    * A force generator that applies a bungee force, where
    * one end is attached to a fixed point in space.
    */
    class ParticleAnchoredBungee : public ParticleAnchoredSpring
    {
    public:
        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle* particle, real duration);
    };
}