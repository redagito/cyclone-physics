#include "BlobDemo.h"

#include <GL/freeglut.h>
#include <cyclonedemo/Timing.h>

#include "Constants.h"

/*
 * The Blob demo.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

 // Method definitions
BlobDemo::BlobDemo()
	:
	xAxis(0), yAxis(0),
	world(PLATFORM_COUNT + BLOB_COUNT, PLATFORM_COUNT)
{
	// Create the blob storage
	blobs = new cyclone::Particle[BLOB_COUNT];
	cyclone::Random r;

	// Create the force generator
	blobForceGenerator.particles = blobs;
	blobForceGenerator.maxAttraction = 20.0f;
	blobForceGenerator.maxReplusion = 10.0f;
	blobForceGenerator.minNaturalDistance = BLOB_RADIUS * 0.75f;
	blobForceGenerator.maxNaturalDistance = BLOB_RADIUS * 1.5f;
	blobForceGenerator.maxDistance = BLOB_RADIUS * 2.5f;
	blobForceGenerator.maxFloat = 2;
	blobForceGenerator.floatHead = 8.0f;

	// Create the platforms
	platforms = new Platform[PLATFORM_COUNT];
	for (unsigned i = 0; i < PLATFORM_COUNT; i++)
	{
		platforms[i].start = cyclone::Vector3(
			double(i % 2) * 10.0f - 5.0f,
			double(i) * 4.0f + ((i % 2) ? 0.0f : 2.0f),
			0);
		platforms[i].start.x += r.randomBinomial(2.0f);
		platforms[i].start.y += r.randomBinomial(2.0f);

		platforms[i].end = cyclone::Vector3(
			double(i % 2) * 10.0f + 5.0f,
			double(i) * 4.0f + ((i % 2) ? 2.0f : 0.0f),
			0);
		platforms[i].end.x += r.randomBinomial(2.0f);
		platforms[i].end.y += r.randomBinomial(2.0f);

		// Make sure the platform knows which particles it
		// should collide with.
		platforms[i].particles = blobs;
		world.getContactGenerators().push_back(platforms + i);
	}

	// Create the blobs.
	Platform* p = platforms + (PLATFORM_COUNT - 2);
	double fraction = (double)1.0 / BLOB_COUNT;
	cyclone::Vector3 delta = p->end - p->start;
	for (unsigned i = 0; i < BLOB_COUNT; i++)
	{
		unsigned me = (i + BLOB_COUNT / 2) % BLOB_COUNT;
		blobs[i].setPosition(
			p->start + delta * (double(me) * 0.8f * fraction + 0.1f) +
			cyclone::Vector3(0, 1.0f + r.randomReal(), 0));

		blobs[i].setVelocity(0, 0, 0);
		blobs[i].setDamping(0.2f);
		blobs[i].setAcceleration(cyclone::Vector3::GRAVITY * 0.4f);
		blobs[i].setMass(1.0f);
		blobs[i].clearAccumulator();

		world.getParticles().push_back(blobs + i);
		world.getForceRegistry().add(blobs + i, &blobForceGenerator);
	}
}

void BlobDemo::reset()
{
	cyclone::Random r;
	Platform* p = platforms + (PLATFORM_COUNT - 2);
	double fraction = (double)1.0 / BLOB_COUNT;
	cyclone::Vector3 delta = p->end - p->start;
	for (unsigned i = 0; i < BLOB_COUNT; i++)
	{
		unsigned me = (i + BLOB_COUNT / 2) % BLOB_COUNT;
		blobs[i].setPosition(
			p->start + delta * (double(me) * 0.8f * fraction + 0.1f) +
			cyclone::Vector3(0, 1.0f + r.randomReal(), 0));
		blobs[i].setVelocity(0, 0, 0);
		blobs[i].clearAccumulator();
	}
}

BlobDemo::~BlobDemo()
{
	delete blobs;
}

void BlobDemo::display()
{
	cyclone::Vector3 pos = blobs[0].getPosition();

	// Clear the view port and set the camera direction
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(pos.x, pos.y, 6.0, pos.x, pos.y, 0.0, 0.0, 1.0, 0.0);

	glColor3f(0, 0, 0);


	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	for (unsigned i = 0; i < PLATFORM_COUNT; i++)
	{
		const cyclone::Vector3& p0 = platforms[i].start;
		const cyclone::Vector3& p1 = platforms[i].end;
		glVertex3f(p0.x, p0.y, p0.z);
		glVertex3f(p1.x, p1.y, p1.z);
	}
	glEnd();

	glColor3f(1, 0, 0);
	for (unsigned i = 0; i < BLOB_COUNT; i++)
	{
		const cyclone::Vector3& p = blobs[i].getPosition();
		glPushMatrix();
		glTranslatef(p.x, p.y, p.z);
		glutSolidSphere(BLOB_RADIUS, 12, 12);
		glPopMatrix();
	}

	cyclone::Vector3 p = blobs[0].getPosition();
	cyclone::Vector3 v = blobs[0].getVelocity() * 0.05f;
	v.trim(BLOB_RADIUS * 0.5f);
	p = p + v;
	glPushMatrix();
	glTranslatef(p.x - BLOB_RADIUS * 0.2f, p.y, BLOB_RADIUS);
	glColor3f(1, 1, 1);
	glutSolidSphere(BLOB_RADIUS * 0.2f, 8, 8);
	glTranslatef(0, 0, BLOB_RADIUS * 0.2f);
	glColor3f(0, 0, 0);
	glutSolidSphere(BLOB_RADIUS * 0.1f, 8, 8);
	glTranslatef(BLOB_RADIUS * 0.4f, 0, -BLOB_RADIUS * 0.2f);
	glColor3f(1, 1, 1);
	glutSolidSphere(BLOB_RADIUS * 0.2f, 8, 8);
	glTranslatef(0, 0, BLOB_RADIUS * 0.2f);
	glColor3f(0, 0, 0);
	glutSolidSphere(BLOB_RADIUS * 0.1f, 8, 8);
	glPopMatrix();
}

void BlobDemo::update()
{
	// Clear accumulators
	world.startFrame();

	// Find the duration of the last frame in seconds
	float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
	if (duration <= 0.0f) return;

	// Recenter the axes
	xAxis *= pow(0.1f, duration);
	yAxis *= pow(0.1f, duration);

	// Move the controlled blob
	blobs[0].addForce(cyclone::Vector3(xAxis, yAxis, 0) * 10.0f);

	// Run the simulation
	world.runPhysics(duration);

	// Bring all the particles back to 2d
	cyclone::Vector3 position;
	for (unsigned i = 0; i < BLOB_COUNT; i++)
	{
		blobs[i].getPosition(&position);
		position.z = 0.0f;
		blobs[i].setPosition(position);
	}

	Application::update();
}

const char* BlobDemo::getTitle()
{
	return "Cyclone > Blob Demo";
}

void BlobDemo::key(unsigned char key)
{
	switch (key)
	{
	case 'w': case 'W':
		yAxis = 1.0;
		break;
	case 's': case 'S':
		yAxis = -1.0;
		break;
	case 'a': case 'A':
		xAxis = -1.0f;
		break;
	case 'd': case 'D':
		xAxis = 1.0f;
		break;
	case 'r': case 'R':
		reset();
		break;
	}
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
	return new BlobDemo();
}