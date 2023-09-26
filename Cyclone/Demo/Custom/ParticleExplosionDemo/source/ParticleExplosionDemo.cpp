#include "ParticleExplosionDemo.h"

#include <GL/freeglut.h>
#include <cyclonedemo/Timing.h>

void ParticleExplosionDemo::fire()
{
	if (fired) return;
	fired = true;

	// Create and register explosions
	int explosionsCount = 1; // random.randomInt(1, 1);
	explosions.reserve(explosionsCount);
	for (int i = 0; i < explosionsCount; ++i)
	{
		cyclone::Explosion explosion;
		// Configure
		explosion.implosionDuration = 8.0;
		explosion.implosionForce = 1000.0;
		explosion.implosionMaxRadius = 100.0;
		explosion.implosionMinRadius = 1.0;
		explosion.concussionDuration = 10.0;
		explosion.peakConcussionForce = 1000.0;
		explosion.shockwaveSpeed = 10.0;
		explosion.shockwaveThickness = 5.0;

		// Add and register
		explosions.push_back(explosion);
		world.registerGlobalForceGenerator(&explosions.back());
	}
}

void ParticleExplosionDemo::reset()
{
	fired = false;
	world.clear();
	explosions.clear();

	fillWithRandomParticles(cyclone::Vector3{ -20 }, cyclone::Vector3{ 20 }, 1.0, 1.0);
}

// Method definitions
ParticleExplosionDemo::ParticleExplosionDemo()
	:
	MassAggregateApplication(2000, cyclone::Vector3{ 1.0, 0.0, 0.0 }, false)
{
	// Camera
	camera.position = cyclone::Vector3{ 0.0, 0.0, -50.0 };

	reset();
}

void ParticleExplosionDemo::updateObjects(double duration)
{
	for (auto& explosion : explosions)
	{
		explosion.updateTimePassed(duration);
	}
}

void ParticleExplosionDemo::initGraphics()
{
	// Call the superclass
	MassAggregateApplication::initGraphics();

	// But override the clear color
	glClearColor(0.6f, 0.9f, 0.95f, 1.0f);
}

const char* ParticleExplosionDemo::getTitle()
{
	return "Cyclone > Particle Explosion Demo";
}

void ParticleExplosionDemo::key(unsigned char key)
{
	switch (key)
	{
	case 'r': case 'R': reset(); break;
	case 'q': case 'Q': fire(); break;
	default: MassAggregateApplication::key(key);
	}
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
	return new ParticleExplosionDemo();
}
