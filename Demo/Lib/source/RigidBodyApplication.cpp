#include "cyclonedemo/RigidBodyApplication.h"

#include <GL/freeglut.h>

#include "cyclonedemo/Timing.h"

RigidBodyApplication::RigidBodyApplication()
	:
	resolver(maxContacts * 8),
	theta(0.0f),
	phi(15.0f),

	renderDebugInfo(false),
	pauseSimulation(true),
	autoPauseSimulation(false)
{
	cData.contactArray = contacts;
}

void RigidBodyApplication::update()
{
	// Find the duration of the last frame in seconds
	float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
	if (duration <= 0.0f) return;
	else if (duration > 0.05f) duration = 0.05f;

	// Exit immediately if we aren't running the simulation
	if (pauseSimulation)
	{
		Application::update();
		return;
	}
	else if (autoPauseSimulation)
	{
		pauseSimulation = true;
		autoPauseSimulation = false;
	}

	// Update the objects
	updateObjects(duration);

	// Perform the contact generation
	generateContacts();

	// Resolve detected contacts
	resolver.resolveContacts(
		cData.contactArray,
		cData.contactCount,
		duration
	);

	Application::update();
}

void RigidBodyApplication::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(18.0f, 0, 0, 0, 0, 0, 0, 1.0f, 0);
	glRotatef(-phi, 0, 0, 1);
	glRotatef(theta, 0, 1, 0);
	glTranslatef(0, -5.0f, 0);
}

void RigidBodyApplication::drawDebug()
{
	if (!renderDebugInfo) return;

	// Recalculate the contacts, so they are current (in case we're
	// paused, for example).
	generateContacts();

	// Render the contacts, if required
	glBegin(GL_LINES);
	for (unsigned i = 0; i < cData.contactCount; i++)
	{
		// Interbody contacts are in green, floor contacts are red.
		if (contacts[i].body[1]) {
			glColor3f(0, 1, 0);
		}
		else {
			glColor3f(1, 0, 0);
		}

		cyclone::Vector3 vec = contacts[i].contactPoint;
		glVertex3f((GLfloat)vec.x, (GLfloat)vec.y, (GLfloat)vec.z);

		vec += contacts[i].contactNormal;
		glVertex3f((GLfloat)vec.x, (GLfloat)vec.y, (GLfloat)vec.z);
	}

	glEnd();
}

void RigidBodyApplication::mouse(int /*button*/, int /*state*/, int x, int y)
{
	// Set the position
	last_x = x;
	last_y = y;
}

void RigidBodyApplication::mouseDrag(int x, int y)
{
	// Update the camera
	theta += (x - last_x) * 0.25f;
	phi += (y - last_y) * 0.25f;

	// Keep it in bounds
	if (phi < -20.0f) phi = -20.0f;
	else if (phi > 80.0f) phi = 80.0f;

	// Remember the position
	last_x = x;
	last_y = y;
}

void RigidBodyApplication::key(unsigned char key)
{
	switch (key)
	{
	case 'R': case 'r':
		// Reset the simulation
		reset();
		return;

	case 'C': case 'c':
		// Toggle rendering of contacts
		renderDebugInfo = !renderDebugInfo;
		return;

	case 'P': case 'p':
		// Toggle running the simulation
		pauseSimulation = !pauseSimulation;
		return;

	case ' ':
		// Advance one frame
		autoPauseSimulation = true;
		pauseSimulation = false;
	}

	Application::key(key);
}
