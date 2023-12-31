#include "cyclone/force/ParticleDrag.h"

#include "cyclone/Vector3.h"
#include "cyclone/Particle.h"

using namespace cyclone;

ParticleDrag::ParticleDrag(double k1, double k2)
    : k1(k1), k2(k2)
{
}

void ParticleDrag::updateForce(Particle* particle, double /*duration*/)
{
    Vector3 force;
    particle->getVelocity(&force);

    // Calculate the total drag coefficient
    double dragCoeff = force.magnitude();
    dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

    // Calculate the final force and apply it
    force.normalise();
    force *= -dragCoeff;
    particle->addForce(force);
}