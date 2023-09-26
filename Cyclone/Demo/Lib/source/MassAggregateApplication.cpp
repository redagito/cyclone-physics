#include "cyclonedemo/MassAggregateApplication.h"

#include <chrono>
#include <GL/freeglut.h>

#include "cyclonedemo/Timing.h"

void MassAggregateApplication::fillWithRandomParticles(const cyclone::Vector3& posFrom, const cyclone::Vector3& posTo, double massFrom, double massTo)
{
	// Setup particles
	for (auto particle : world.getParticles())
	{
		particle->setMass(random.randomReal(massFrom, massTo));
		particle->setPosition(random.randomVector(posFrom, posTo));
		particle->setDamping(0.9);
		particle->setAcceleration(0.0);
		particle->setVelocity(0.0);
	}
}

MassAggregateApplication::MassAggregateApplication(unsigned int particleCount, const cyclone::Vector3& particleColor, bool withGround)
	:
	world(particleCount * 10),
	particleColor(particleColor)
{
	particleArray = new cyclone::Particle[particleCount];
	for (unsigned i = 0; i < particleCount; i++)
	{
		world.getParticles().push_back(particleArray + i);
	}

	if (withGround)
	{
		groundContactGenerator.init(&world.getParticles());
		world.getContactGenerators().push_back(&groundContactGenerator);
	}
}

MassAggregateApplication::~MassAggregateApplication()
{
	delete[] particleArray;
}

void MassAggregateApplication::initGraphics()
{
	// Call the superclass
	Application::initGraphics();
}

void MassAggregateApplication::display()
{
	// Clear the view port and set the camera direction
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.lookAt.x, camera.lookAt.y, camera.lookAt.z,
		camera.up.x, camera.up.y, camera.up.z);

	glRotatef(-phi, 0, 0, 1);
	glRotatef(theta, 0, 1, 0);

	// Set particle color and draw all particles in the world
	glColor3f((GLfloat)particleColor.x, (GLfloat)particleColor.y, (GLfloat)particleColor.z);

	cyclone::Particles& particles = world.getParticles();
	for (cyclone::Particles::iterator p = particles.begin();
		p != particles.end();
		p++)
	{
		cyclone::Particle* particle = *p;
		const cyclone::Vector3& pos = particle->getPosition();
		glPushMatrix();
		glTranslatef((GLfloat)pos.x, (GLfloat)pos.y, (GLfloat)pos.z);
		glutSolidSphere(0.1f, 20, 10);
		glPopMatrix();
	}
}

void MassAggregateApplication::updateObjects(double /*duration*/)
{
}

void MassAggregateApplication::update()
{
	// Clear accumulators
	world.startFrame();

	// Find the duration of the last frame in seconds
	float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
	if (duration <= 0.0f) return;
	else if (duration > 0.05f) duration = 0.05f;

	updateObjects(duration);

	// Run the simulation
	world.runPhysics(duration);

	Application::update();
}