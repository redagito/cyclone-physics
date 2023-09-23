#include "cyclone/force/ParticleForceRegistry.h"
#include "cyclone/force/ParticleForceGenerator.h"

using namespace cyclone;

void ParticleForceRegistry::updateForces(double duration)
{
    for (const auto& registration : registrations)
    {
        registration.fg->updateForce(registration.particle, duration);
    }
}

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg)
{
    ParticleForceRegistry::ParticleForceRegistration registration;
    registration.particle = particle;
    registration.fg = fg;
    registrations.push_back(registration);
}