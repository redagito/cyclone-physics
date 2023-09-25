#include "cyclone/force/ParticleBuoyancy.h"

#include "cyclone/Particle.h"

using namespace cyclone;

ParticleBuoyancy::ParticleBuoyancy(double maxDepth,
    double volume,
    double waterHeight,
    double liquidDensity)
    :
    maxDepth(maxDepth), volume(volume),
    waterHeight(waterHeight), liquidDensity(liquidDensity)
{
}

void ParticleBuoyancy::updateForce(Particle* particle, double /*duration*/)
{
    // Calculate the submersion depth
    double depth = particle->getPosition().y;

    // Check if we're out of the water
    if (depth >= waterHeight + maxDepth) return;
    Vector3 force(0, 0, 0);

    // Check if we're at maximum depth
    if (depth <= waterHeight - maxDepth)
    {
        force.y = liquidDensity * volume;
        particle->addForce(force);
        return;
    }

    // Otherwise we are partly submerged
    force.y = liquidDensity * volume *
        (depth - maxDepth - waterHeight) / (2 * maxDepth);
    particle->addForce(force);
}