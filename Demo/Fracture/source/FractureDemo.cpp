#include "FractureDemo.h"

/**
 * The fracture demo.
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

// Method definitions
FractureDemo::FractureDemo()
	:
	RigidBodyApplication()
{
	// Create the ball.
	ball.body = new cyclone::RigidBody();
	ball.radius = 0.25f;
	ball.body->setMass(5.0f);
	ball.body->setDamping(0.9f, 0.9f);
	cyclone::Matrix3 it;
	it.setDiagonal(5.0f, 5.0f, 5.0f);
	ball.body->setInertiaTensor(it);
	ball.body->setAcceleration(cyclone::Vector3::GRAVITY);

	ball.body->setCanSleep(false);
	ball.body->setAwake(true);

	// Set up the initial block
	reset();
}

const char* FractureDemo::getTitle()
{
	return "Cyclone > Fracture Demo";
}

void FractureDemo::generateContacts()
{
	hit = false;

	// Create the ground plane data
	cyclone::CollisionPlane plane;
	plane.direction = cyclone::Vector3(0, 1, 0);
	plane.offset = 0;

	// Set up the collision data structure
	cData.reset(maxContacts);
	cData.friction = (double)0.9;
	cData.restitution = (double)0.2;
	cData.tolerance = (double)0.1;

	// Perform collision detection
	cyclone::Matrix4 transform, otherTransform;
	cyclone::Vector3 position, otherPosition;
	for (Block* block = blocks; block < blocks + MAX_BLOCKS; block++)
	{
		if (!block->exists) continue;

		// Check for collisions with the ground plane
		if (!cData.hasMoreContacts()) return;
		cyclone::CollisionDetector::boxAndHalfSpace(*block, plane, &cData);

		if (ball_active)
		{
			// And with the sphere
			if (!cData.hasMoreContacts()) return;
			if (cyclone::CollisionDetector::boxAndSphere(*block, ball, &cData))
			{
				hit = true;
				fracture_contact = cData.contactCount - 1;
			}
		}

		// Check for collisions with each other box
		for (Block* other = block + 1; other < blocks + MAX_BLOCKS; other++)
		{
			if (!other->exists) continue;

			if (!cData.hasMoreContacts()) return;
			cyclone::CollisionDetector::boxAndBox(*block, *other, &cData);
		}
	}

	// Check for sphere ground collisions
	if (ball_active)
	{
		if (!cData.hasMoreContacts()) return;
		cyclone::CollisionDetector::sphereAndHalfSpace(ball, plane, &cData);
	}
}

void FractureDemo::reset()
{
	// Only the first block exists
	blocks[0].exists = true;
	for (Block* block = blocks + 1; block < blocks + MAX_BLOCKS; block++)
	{
		block->exists = false;
	}

	// Set the first block
	blocks[0].halfSize = cyclone::Vector3(4, 4, 4);
	blocks[0].body->setPosition(0, 7, 0);
	blocks[0].body->setOrientation(1, 0, 0, 0);
	blocks[0].body->setVelocity(0, 0, 0);
	blocks[0].body->setRotation(0, 0, 0);
	blocks[0].body->setMass(100.0f);
	cyclone::Matrix3 it;
	it.setBlockInertiaTensor(blocks[0].halfSize, 100.0f);
	blocks[0].body->setInertiaTensor(it);
	blocks[0].body->setDamping(0.9f, 0.9f);
	blocks[0].body->calculateDerivedData();
	blocks[0].calculateInternals();

	blocks[0].body->setAcceleration(cyclone::Vector3::GRAVITY);
	blocks[0].body->setAwake(true);
	blocks[0].body->setCanSleep(true);


	ball_active = true;

	// Set up the ball
	ball.body->setPosition(0, 5.0f, 20.0f);
	ball.body->setOrientation(1, 0, 0, 0);
	ball.body->setVelocity(
		random.randomBinomial(4.0f),
		random.randomReal(1.0f, 6.0f),
		-20.0f
	);
	ball.body->setRotation(0, 0, 0);
	ball.body->calculateDerivedData();
	ball.body->setAwake(true);
	ball.calculateInternals();

	hit = false;

	// Reset the contacts
	cData.contactCount = 0;
}

void FractureDemo::update()
{
	RigidBodyApplication::update();

	// Handle fractures.
	if (hit)
	{
		blocks[0].divideBlock(
			cData.contactArray[fracture_contact],
			blocks,
			blocks + 1
		);
		ball_active = false;
	}
}

void FractureDemo::updateObjects(double duration)
{
	for (Block* block = blocks; block < blocks + MAX_BLOCKS; block++)
	{
		if (block->exists)
		{
			block->body->integrate(duration);
			block->calculateInternals();
		}
	}

	if (ball_active)
	{
		ball.body->integrate(duration);
		ball.calculateInternals();
	}
}

void FractureDemo::display()
{
	const static GLfloat lightPosition[] = { 0.7f,1,0.4f,0 };

	RigidBodyApplication::display();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_NORMALIZE);
	for (Block* block = blocks; block < blocks + MAX_BLOCKS; block++)
	{
		if (block->exists) block->render();
	}
	glDisable(GL_NORMALIZE);

	if (ball_active)
	{
		glColor3f(0.4f, 0.7f, 0.4f);
		glPushMatrix();
		cyclone::Vector3 pos = ball.body->getPosition();
		glTranslatef(pos.x, pos.y, pos.z);
		glutSolidSphere(0.25f, 16, 8);
		glPopMatrix();
	}

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

	RigidBodyApplication::drawDebug();
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
	return new FractureDemo();
}