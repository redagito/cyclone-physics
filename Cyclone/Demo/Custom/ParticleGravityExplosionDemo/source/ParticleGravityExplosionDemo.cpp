#include "ParticleGravityExplosionDemo.h"

#include <GL/freeglut.h>
#include <cyclonedemo/Timing.h>

void ParticleGravityExplosionDemo::fire()
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
		explosion.detonation.y = 10.0;
		explosion.implosionDuration = 3.0;
		explosion.implosionForce = 10000.0;
		explosion.implosionMaxRadius = 1000.0;
		explosion.implosionMinRadius = 1.0;
		explosion.concussionDuration = 20.0;
		explosion.peakConcussionForce = 10000.0;
		explosion.shockwaveSpeed = 10.0;
		explosion.shockwaveThickness = 10.0;

		// Add and register
		explosions.push_back(explosion);
		world.registerGlobalForceGenerator(&explosions.back());
	}
}

void ParticleGravityExplosionDemo::reset()
{
	fired = false;
	world.clear();
	explosions.clear();

	world.registerGlobalForceGenerator(&gravity);
	fillWithRandomParticles(cyclone::Vector3{ -20.0, 0.0, -20.0 }, cyclone::Vector3{ 20.0, 80.0, 20.0 }, 1.0, 1.0);

	MassAggregateApplication::reset();
}

// Method definitions
ParticleGravityExplosionDemo::ParticleGravityExplosionDemo()
	:
	MassAggregateApplication(1000, cyclone::Vector3{ 1.0, 0.0, 0.0 }),
	gravity(cyclone::Vector3::GRAVITY)
{
	// Camera
	camera.position = cyclone::Vector3{ 0.0, 5.0, -30.0 };

	reset();
}

void ParticleGravityExplosionDemo::updateObjects(double duration)
{
	for (auto& explosion : explosions)
	{
		explosion.updateTimePassed(duration);
	}
}

void ParticleGravityExplosionDemo::initGraphics()
{
	// Call the superclass
	MassAggregateApplication::initGraphics();

	// But override the clear color
	glClearColor(0.6f, 0.9f, 0.95f, 1.0f);
}

const char* ParticleGravityExplosionDemo::getTitle()
{
	return "Cyclone > Particle Explosion Demo";
}

void ParticleGravityExplosionDemo::key(unsigned char key)
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
	return new ParticleGravityExplosionDemo();
}
