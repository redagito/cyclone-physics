#include "ExplosionDemo.h"

/*
 * The explosion demo.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include <cyclonedemo/Timing.h>

#include <GL/freeglut.h>

 // Holds a transform matrix for rendering objects
 // reflected in the floor.
GLfloat floorMirror[16] =
{
	1, 0, 0, 0,
	0, -1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

// Method definitions
ExplosionDemo::ExplosionDemo()
	:
	RigidBodyApplication(),
	editMode(false),
	upMode(false)
{
	// Reset the position of the boxes
	reset();
}

const char* ExplosionDemo::getTitle()
{
	return "Cyclone > Explosion Demo";
}

void ExplosionDemo::fire()
{
	cyclone::Vector3 pos = ballData[0].body->getPosition();
	pos.normalise();

	ballData[0].body->addForce(pos * -10000.0f);
}

void ExplosionDemo::reset()
{
	Box* box = boxData;

	box++->setState(cyclone::Vector3(0, 3, 0),
		cyclone::Quaternion(),
		cyclone::Vector3(4, 1, 1),
		cyclone::Vector3(0, 1, 0));

	if (boxes > 1)
	{
		box++->setState(cyclone::Vector3(0, 4.75, 2),
			cyclone::Quaternion(1.0, 0.1, 0.05, 0.01),
			cyclone::Vector3(1, 1, 4),
			cyclone::Vector3(0, 1, 0));
	}

	// Create the random objects
	cyclone::Random random;
	for (; box < boxData + boxes; box++)
	{
		box->random(&random);
	}

	for (Ball* ball = ballData; ball < ballData + balls; ball++)
	{
		ball->random(&random);
	}

	// Reset the contacts
	cData.contactCount = 0;
}

void ExplosionDemo::generateContacts()
{
	// Note that this method makes a lot of use of early returns to avoid
	// processing lots of potential contacts that it hasn't got room to
	// store.

	// Create the ground plane data
	cyclone::CollisionPlane plane;
	plane.direction = cyclone::Vector3(0, 1, 0);
	plane.offset = 0;

	// Set up the collision data structure
	cData.reset(maxContacts);
	cData.friction = (double)0.9;
	cData.restitution = (double)0.6;
	cData.tolerance = (double)0.1;

	// Perform exhaustive collision detection
	cyclone::Matrix4 transform, otherTransform;
	cyclone::Vector3 position, otherPosition;
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		// Check for collisions with the ground plane
		if (!cData.hasMoreContacts()) return;
		cyclone::CollisionDetector::boxAndHalfSpace(*box, plane, &cData);

		// Check for collisions with each other box
		for (Box* other = box + 1; other < boxData + boxes; other++)
		{
			if (!cData.hasMoreContacts()) return;
			cyclone::CollisionDetector::boxAndBox(*box, *other, &cData);

			if (cyclone::IntersectionTests::boxAndBox(*box, *other))
			{
				box->isOverlapping = other->isOverlapping = true;
			}
		}

		// Check for collisions with each ball
		for (Ball* other = ballData; other < ballData + balls; other++)
		{
			if (!cData.hasMoreContacts()) return;
			cyclone::CollisionDetector::boxAndSphere(*box, *other, &cData);
		}
	}

	for (Ball* ball = ballData; ball < ballData + balls; ball++)
	{
		// Check for collisions with the ground plane
		if (!cData.hasMoreContacts()) return;
		cyclone::CollisionDetector::sphereAndHalfSpace(*ball, plane, &cData);

		for (Ball* other = ball + 1; other < ballData + balls; other++)
		{
			// Check for collisions with the ground plane
			if (!cData.hasMoreContacts()) return;
			cyclone::CollisionDetector::sphereAndSphere(*ball, *other, &cData);
		}
	}
}

void ExplosionDemo::updateObjects(double duration)
{
	// Update the physics of each box in turn
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		// Run the physics
		box->body->integrate(duration);
		box->calculateInternals();
		box->isOverlapping = false;
	}

	// Update the physics of each ball in turn
	for (Ball* ball = ballData; ball < ballData + balls; ball++)
	{
		// Run the physics
		ball->body->integrate(duration);
		ball->calculateInternals();
	}
}


void ExplosionDemo::initGraphics()
{
	GLfloat lightAmbient[] = { 0.8f,0.8f,0.8f,1.0f };
	GLfloat lightDiffuse[] = { 0.9f,0.95f,1.0f,1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	glEnable(GL_LIGHT0);

	Application::initGraphics();
}

void ExplosionDemo::display()
{
	const static GLfloat lightPosition[] = { 1,-1,0,0 };
	const static GLfloat lightPositionMirror[] = { 1,1,0,0 };

	// Update the transform matrices of each box in turn
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		box->calculateInternals();
		box->isOverlapping = false;
	}

	// Update the transform matrices of each ball in turn
	for (Ball* ball = ballData; ball < ballData + balls; ball++)
	{
		// Run the physics
		ball->calculateInternals();
	}

	// Clear the viewport and set the camera direction
	RigidBodyApplication::display();

	// Render each element in turn as a shadow
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glPushMatrix();
	glMultMatrixf(floorMirror);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		box->render();
	}
	for (Ball* ball = ballData; ball < ballData + balls; ball++)
	{
		ball->render();
	}
	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);

	// Draw some scale circles
	glColor3f(0.75, 0.75, 0.75);
	for (unsigned i = 1; i < 20; i++)
	{
		glBegin(GL_LINE_LOOP);
		for (unsigned j = 0; j < 32; j++)
		{
			float theta = 3.1415926f * j / 16.0f;
			glVertex3f(i * cosf(theta), 0.0f, i * sinf(theta));
		}
		glEnd();
	}
	glBegin(GL_LINES);
	glVertex3f(-20, 0, 0);
	glVertex3f(20, 0, 0);
	glVertex3f(0, 0, -20);
	glVertex3f(0, 0, 20);
	glEnd();

	// Render each shadow in turn
	glEnable(GL_BLEND);
	glColor4f(0, 0, 0, 0.1f);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		box->renderShadow();
	}
	for (Ball* ball = ballData; ball < ballData + balls; ball++)
	{
		ball->renderShadow();
	}
	glDisable(GL_BLEND);

	// Render the boxes themselves
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionMirror);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	for (Box* box = boxData; box < boxData + boxes; box++)
	{
		box->render();
	}
	for (Ball* ball = ballData; ball < ballData + balls; ball++)
	{
		ball->render();
	}
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Finish the frame, rendering any additional information
	drawDebug();
}

void ExplosionDemo::mouseDrag(int x, int y)
{
	if (editMode)
	{
		boxData[0].body->setPosition(boxData[0].body->getPosition() +
			cyclone::Vector3(
				(x - last_x) * 0.125f,
				0,
				(y - last_y) * 0.125f
			)
		);
		boxData[0].body->calculateDerivedData();
	}
	else if (upMode)
	{
		boxData[0].body->setPosition(boxData[0].body->getPosition() +
			cyclone::Vector3(
				0,
				(y - last_y) * 0.125f,
				0
			)
		);
		boxData[0].body->calculateDerivedData();
	}
	else
	{
		RigidBodyApplication::mouseDrag(x, y);
	}

	// Remember the position
	last_x = x;
	last_y = y;
}


void ExplosionDemo::key(unsigned char key)
{
	switch (key)
	{
	case 'e': case 'E':
		editMode = !editMode;
		upMode = false;
		return;

	case 't': case 'T':
		upMode = !upMode;
		editMode = false;
		return;

	case 'w': case 'W':
		for (Box* box = boxData; box < boxData + boxes; box++)
			box->body->setAwake();
		for (Ball* ball = ballData; ball < ballData + balls; ball++)
			ball->body->setAwake();
		return;

	case 'q': case 'Q':
		fire();
		return;
	}

	RigidBodyApplication::key(key);
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
	return new ExplosionDemo();
}