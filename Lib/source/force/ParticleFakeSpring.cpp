#include "cyclone/force/ParticleFakeSpring.h"
#include "cyclone/Vector3.h"
#include "cyclone/Particle.h"

using namespace cyclone;

ParticleFakeSpring::ParticleFakeSpring(Vector3* anchor, double sc, double d)
    : anchor(anchor), springConstant(sc), damping(d)
{
}

void ParticleFakeSpring::updateForce(Particle* particle, double duration)
{
    // Check that we do not have infinite mass
    if (!particle->hasFiniteMass()) return;

    // Calculate the relative position of the particle to the anchor
    Vector3 position;
    particle->getPosition(&position);
    position -= *anchor;

    // Calculate the constants and check they are in bounds.
    double gamma = 0.5f * std::sqrt(4 * springConstant - damping * damping);
    if (gamma == 0.0f) return;
    Vector3 c = position * (damping / (2.0f * gamma)) +
        particle->getVelocity() * (1.0f / gamma);

    // Calculate the target position
    Vector3 target = position * std::cos(gamma * duration) +
        c * std::sin(gamma * duration);
    target *= std::exp(-0.5f * duration * damping);

    // Calculate the resulting acceleration and therefore the force
    Vector3 accel = (target - position) * ((double)1.0 / (duration * duration)) -
        particle->getVelocity() * ((double)1.0 / duration);
    particle->addForce(accel * particle->getMass());
}