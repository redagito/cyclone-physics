#include "ParticleGravityDemo.h"

#include <GL/freeglut.h>

#include <cyclonedemo/Timing.h>

// Method definitions
ParticlesDemo::ParticlesDemo()
	:
	MassAggregateApplication(1000),
	gravity(cyclone::Vector3{0.0, -1.0, 0.0})
{
	cyclone::Random rand;
	for (auto particle : world.getParticles())
	{
		particle->setMass(rand.randomReal(0.1, 100.0));
		particle->setPosition(rand.randomVector(cyclone::Vector3{ -5.0, 0.0, -5.0 }, cyclone::Vector3{ 5.0, 20.0, 5.0 }));
		world.getForceRegistry().add(particle, &gravity);
	}
}

ParticlesDemo::~ParticlesDemo()
{
}

void ParticlesDemo::initGraphics()
{
	// Call the superclass
	MassAggregateApplication::initGraphics();

	// But override the clear color
	glClearColor(0.6f, 0.9f, 0.95f, 1.0f);
}

const char* ParticlesDemo::getTitle()
{
	return "Cyclone > Fireworks Demo";
}

void ParticlesDemo::update()
{
	MassAggregateApplication::update();
}

void ParticlesDemo::display()
{
	MassAggregateApplication::display();
}

void ParticlesDemo::key(unsigned char key)
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
	return new ParticlesDemo();
}
