#include "ParticleGravityWellDemo.h"

#include <chrono>

#include <GL/freeglut.h>
#include <cyclonedemo/Timing.h>


void ParticleGravityWellDemo::reset()
{
	world.clear();
	gravityWells.clear();

	// Setup particles
	auto s = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
	cyclone::Random rand{ (unsigned int)(s.count() % 10000000)};

	for (auto particle : world.getParticles())
	{
		particle->setMass(rand.randomReal(0.1, 100.0));
		particle->setPosition(rand.randomVector(cyclone::Vector3{ -20.0, -20.0, -20.0 }, cyclone::Vector3{ 20.0, 20.0, 20.0 }));
		particle->setDamping(0.9);
	}

	// Create and register gravity wells
	int wellCount = rand.randomInt(5, 20);
	gravityWells.reserve(wellCount);
	for (int i = 0; i < wellCount; ++i)
	{
		gravityWells.push_back(
			cyclone::ParticleGravityWell(rand.randomReal(10.0, 90.0),
				rand.randomVector(cyclone::Vector3{ -20.0, -20.0, -20.0 },
					cyclone::Vector3{ 20.0, 20.0, 20.0 }),
				rand.randomReal(1.0, 3.0)));
		world.registerGlobalForceGenerator(&gravityWells.back());
	}
}

// Method definitions
ParticleGravityWellDemo::ParticleGravityWellDemo()
	:
	MassAggregateApplication(2000, cyclone::Vector3{ 1.0, 0.0, 0.0 }, false)
{
	// Camera
	camera.position = cyclone::Vector3{ 0.0, 0.0, -50.0 };

	reset();
}

void ParticleGravityWellDemo::initGraphics()
{
	// Call the superclass
	MassAggregateApplication::initGraphics();

	// But override the clear color
	glClearColor(0.6f, 0.9f, 0.95f, 1.0f);
}

const char* ParticleGravityWellDemo::getTitle()
{
	return "Cyclone > Particle Gravity Well Demo";
}

void ParticleGravityWellDemo::key(unsigned char key)
{
	switch (key)
	{
	case 'r': case 'R': reset(); break;
	default: MassAggregateApplication::key(key);
	}
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
	return new ParticleGravityWellDemo();
}
