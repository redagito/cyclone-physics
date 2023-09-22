#include "cyclone/force/ParticleAnchoredBungee.h"
#include "cyclone/Particle.h"

using namespace cyclone;

void ParticleAnchoredBungee::updateForce(Particle* particle, real /*duration*/)
{
    // Calculate the vector of the spring
    Vector3 force;
    particle->getPosition(&force);
    force -= *anchor;

    // Calculate the magnitude of the force
    real magnitude = force.magnitude();
    if (magnitude < restLength) return;

    magnitude = magnitude - restLength;
    magnitude *= springConstant;

    // Calculate the final force and apply it
    force.normalise();
    force *= -magnitude;
    particle->addForce(force);
}