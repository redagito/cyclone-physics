#pragma once

#include "cyclonedemo/Application.h"

/**
 * This application adds additional functionality used in the mass-aggregate demos.
 */
class MassAggregateApplication : public Application
{
protected:
    cyclone::ParticleWorld world;
    cyclone::Particle *particleArray = nullptr;
    cyclone::GroundContacts groundContactGenerator;

public:
    MassAggregateApplication(unsigned int particleCount);
    virtual ~MassAggregateApplication();

    /** Update the particle positions. */
    virtual void update();

    /** Sets up the graphic rendering. */
    virtual void initGraphics();

    /** Display the particles. */
    virtual void display();
};