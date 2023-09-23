#include "BigBallisticDemo.h"

/*
 * The BigBallistic demo.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include <GL/freeglut.h>

#include <cyclonedemo/Timing.h>

 // Method definitions
BigBallisticDemo::BigBallisticDemo()
	:
	RigidBodyApplication(),
	currentShotType(LASER)
{
	pauseSimulation = false;
	reset();
}


void BigBallisticDemo::initGraphics()
{
	GLfloat lightAmbient[] = { 0.8f,0.8f,0.8f,1.0f };
	GLfloat lightDiffuse[] = { 0.9f,0.95f,1.0f,1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	glEnable(GL_LIGHT0);

	Application::initGraphics();
}

void BigBallisticDemo::reset()
{
	// Make all shots unused
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		shot->type = UNUSED;
	}

	// Initialise the box
	double z = 20.0f;
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		box->setState(z);
		z += 15.0f;
	}
}

const char* BigBallisticDemo::getTitle()
{
	return "Cyclone > Big Ballistic Demo";
}

void BigBallisticDemo::fire()
{
	// Find the first available round.
	AmmoRound* shot = nullptr;
	for (shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type == UNUSED) break;
	}

	// If we didn't find a round, then exit - we can't fire.
	if (shot >= ammo + ammoRounds) return;

	// Set the shot
	shot->setState(currentShotType);

}

void BigBallisticDemo::updateObjects(double duration)
{
	// Update the physics of each particle in turn
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type != UNUSED)
		{
			// Run the physics
			shot->body->integrate(duration);
			shot->calculateInternals();

			// Check if the particle is now invalid
			if (shot->body->getPosition().y < 0.0f ||
				shot->startTime + 5000 < TimingData::get().lastFrameTimestamp ||
				shot->body->getPosition().z > 200.0f)
			{
				// We simply set the shot type to be unused, so the
				// memory it occupies can be reused by another shot.
				shot->type = UNUSED;
			}
		}
	}

	// Update the boxes
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		// Run the physics
		box->body->integrate(duration);
		box->calculateInternals();
	}
}

void BigBallisticDemo::display()
{
	const static GLfloat lightPosition[] = { -1,1,0,0 };

	// Clear the viewport and set the camera direction
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(-25.0, 8.0, 5.0, 0.0, 5.0, 22.0, 0.0, 1.0, 0.0);

	// Draw a sphere at the firing point, and add a shadow projected
	// onto the ground plane.
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glutSolidSphere(0.1f, 5, 5);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glColor3f(0.75f, 0.75f, 0.75f);
	glScalef(1.0f, 0.1f, 1.0f);
	glutSolidSphere(0.1f, 5, 5);
	glPopMatrix();

	// Draw some scale lines
	glColor3f(0.75f, 0.75f, 0.75f);
	glBegin(GL_LINES);
	for (unsigned i = 0; i < 200; i += 10)
	{
		glVertex3f(-5.0f, 0.0f, i);
		glVertex3f(5.0f, 0.0f, i);
	}
	glEnd();

	// Render each particle in turn
	glColor3f(1, 0, 0);
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type != UNUSED)
		{
			shot->render();
		}
	}

	// Render the box
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 0, 0);
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		box->render();
	}
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Render the description
	glColor3f(0.0f, 0.0f, 0.0f);
	renderText(10.0f, 34.0f, "Click: Fire\n1-5: Select Ammo");

	// Render the name of the current shot type
	switch (currentShotType)
	{
	case PISTOL: renderText(10.0f, 10.0f, "Current Ammo: Pistol"); break;
	case ARTILLERY: renderText(10.0f, 10.0f, "Current Ammo: Artillery"); break;
	case FIREBALL: renderText(10.0f, 10.0f, "Current Ammo: Fireball"); break;
	case LASER: renderText(10.0f, 10.0f, "Current Ammo: Laser"); break;
	case GRANADE: renderText(10.0f, 10.0f, "Current Ammo: Granade"); break;
	}
}

void BigBallisticDemo::generateContacts()
{
	// Create the ground plane data
	cyclone::CollisionPlane plane;
	plane.direction = cyclone::Vector3(0, 1, 0);
	plane.offset = 0;

	// Set up the collision data structure
	cData.reset(maxContacts);
	cData.friction = (double)0.9;
	cData.restitution = (double)0.1;
	cData.tolerance = (double)0.1;

	// Check ground plane collisions
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		if (!cData.hasMoreContacts()) return;
		cyclone::CollisionDetector::boxAndHalfSpace(*box, plane, &cData);


		// Check for collisions with each shot
		for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
		{
			if (shot->type != UNUSED)
			{
				if (!cData.hasMoreContacts()) return;

				// When we get a collision, remove the shot
				if (cyclone::CollisionDetector::boxAndSphere(*box, *shot, &cData))
				{
					shot->type = UNUSED;
				}
			}
		}
	}

	// NB We aren't checking box-box collisions.
}

void BigBallisticDemo::mouse(int button, int state, int x, int y)
{
	// Fire the current weapon.
	if (state == GLUT_DOWN) fire();
}

void BigBallisticDemo::key(unsigned char key)
{
	switch (key)
	{
	case '1': currentShotType = PISTOL; break;
	case '2': currentShotType = ARTILLERY; break;
	case '3': currentShotType = FIREBALL; break;
	case '4': currentShotType = LASER; break;
	case '5': currentShotType = GRANADE; break;

	case 'r': case 'R': reset(); break;
	}
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
	return new BigBallisticDemo();
}