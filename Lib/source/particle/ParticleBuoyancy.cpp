#include "cyclone/particle/ParticleBuoyancy.h"

#include "cyclone/particle/Particle.h"

using namespace cyclone;

ParticleBuoyancy::ParticleBuoyancy(real maxDepth,
    real volume,
    real waterHeight,
    real liquidDensity)
    :
    maxDepth(maxDepth), volume(volume),
    waterHeight(waterHeight), liquidDensity(liquidDensity)
{
}

void ParticleBuoyancy::updateForce(Particle* particle, real /*duration*/)
{
    // Calculate the submersion depth
    real depth = particle->getPosition().y;

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