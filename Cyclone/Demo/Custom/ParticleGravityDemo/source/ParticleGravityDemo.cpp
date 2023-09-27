#include "ParticleGravityDemo.h"

#include <GL/freeglut.h>

#include <cyclonedemo/Timing.h>

// Method definitions
ParticleGravityDemo::ParticleGravityDemo()
	:
	MassAggregateApplication(1000),
	gravity(cyclone::Vector3{ 0.0, -5.0, 0.0 })
{
	// Camera
	camera.position = cyclone::Vector3{ 0.0, 5.0, -10.0 };

	// Setup particles
	cyclone::Random rand;
	for (auto particle : world.getParticles())
	{
		particle->setMass(rand.randomReal(0.1, 100.0));
		particle->setPosition(rand.randomVector(cyclone::Vector3{ -5.0, 0.0, -5.0 }, cyclone::Vector3{ 5.0, 20.0, 5.0 }));
	}

	// Register gravity
	world.registerGlobalForceGenerator(&gravity);
}

ParticleGravityDemo::~ParticleGravityDemo()
{
}

void ParticleGravityDemo::initGraphics()
{
	// Call the superclass
	MassAggregateApplication::initGraphics();

	// But override the clear color
	glClearColor(0.6f, 0.9f, 0.95f, 1.0f);
}

const char* ParticleGravityDemo::getTitle()
{
	return "Cyclone > Particle Gravity Demo";
}

void ParticleGravityDemo::display()
{
	MassAggregateApplication::display();
}

void ParticleGravityDemo::key(unsigned char key)
{
	switch (key)
	{
	default: MassAggregateApplication::key(key);
	}
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
	return new ParticleGravityDemo();
}
