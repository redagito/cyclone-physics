#pragma once

#include "cyclonedemo/Application.h"
#include <cyclone/Cyclone.h>

/**
 * This application adds additional functionality used in the mass-aggregate demos.
 */
class MassAggregateApplication : public Application
{
protected:
	cyclone::ParticleWorld world;
	cyclone::Particle* particleArray = nullptr;
	cyclone::GroundContacts groundContactGenerator;
	cyclone::ParticleGravity gravity;
	cyclone::Vector3 particleColor;

public:
	MassAggregateApplication(unsigned int particleCount, const cyclone::Vector3& particleColor = cyclone::Vector3{0.9, 0.1, 0.1});
	virtual ~MassAggregateApplication();

	/** Update the particle positions. */
	virtual void update();

	/** Sets up the graphic rendering. */
	virtual void initGraphics();

	/** Display the particles. */
	virtual void display();
};