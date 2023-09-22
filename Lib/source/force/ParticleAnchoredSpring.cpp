#include "cyclone/force/ParticleAnchoredSpring.h"
#include "cyclone/Particle.h"

using namespace cyclone;

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3* anchor,
    real sc, real rl)
    : anchor(anchor), springConstant(sc), restLength(rl)
{
}

void ParticleAnchoredSpring::init(Vector3* anchr, real springConst,
    real restLen)
{
    anchor = anchr;
    springConstant = springConst;
    restLength = restLen;
}

void ParticleAnchoredSpring::updateForce(Particle* particle, real /*duration*/)
{
    // Calculate the vector of the spring
    Vector3 force;
    particle->getPosition(&force);
    force -= *anchor;

    // Calculate the magnitude of the force
    real magnitude = force.magnitude();
    magnitude = (restLength - magnitude) * springConstant;

    // Calculate the final force and apply it
    force.normalise();
    force *= magnitude;
    particle->addForce(force);
}