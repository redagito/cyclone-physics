#include "cyclone/particle/ParticleDrag.h"

#include "cyclone/Vector3.h"
#include "cyclone/particle/Particle.h"

using namespace cyclone;

ParticleDrag::ParticleDrag(real k1, real k2)
    : k1(k1), k2(k2)
{
}

void ParticleDrag::updateForce(Particle* particle, real /*duration*/)
{
    Vector3 force;
    particle->getVelocity(&force);

    // Calculate the total drag coefficient
    real dragCoeff = force.magnitude();
    dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

    // Calculate the final force and apply it
    force.normalise();
    force *= -dragCoeff;
    particle->addForce(force);
}