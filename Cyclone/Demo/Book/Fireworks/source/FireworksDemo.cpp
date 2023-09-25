#include "FireworksDemo.h"

/*
 * The fireworks demo.
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
#include <cstdio>

#include <cyclonedemo/Application.h>
#include <cyclonedemo/Timing.h>

#include "Payload.h"

// Method definitions
FireworksDemo::FireworksDemo()
	:
	nextFirework(0)
{
	// Make all shots unused
	for (Firework* firework = fireworks;
		firework < fireworks + maxFireworks;
		firework++)
	{
		firework->type = 0;
	}

	// Create the firework types
	initFireworkRules();
}

FireworksDemo::~FireworksDemo()
{
}

void FireworksDemo::initFireworkRules()
{
	// Go through the firework types and create their rules.
	rules[0].init(2);
	rules[0].setParameters(
		1, // type
		0.5f, 1.4f, // age range
		cyclone::Vector3(-5, 25, -5), // min velocity
		cyclone::Vector3(5, 28, 5), // max velocity
		0.1 // damping
	);
	rules[0].payloads[0].set(3, 5);
	rules[0].payloads[1].set(5, 5);

	rules[1].init(1);
	rules[1].setParameters(
		2, // type
		0.5f, 1.0f, // age range
		cyclone::Vector3(-5, 10, -5), // min velocity
		cyclone::Vector3(5, 20, 5), // max velocity
		0.8 // damping
	);
	rules[1].payloads[0].set(4, 2);

	rules[2].init(0);
	rules[2].setParameters(
		3, // type
		0.5f, 1.5f, // age range
		cyclone::Vector3(-5, -5, -5), // min velocity
		cyclone::Vector3(5, 5, 5), // max velocity
		0.1 // damping
	);

	rules[3].init(0);
	rules[3].setParameters(
		4, // type
		0.25f, 0.5f, // age range
		cyclone::Vector3(-20, 5, -5), // min velocity
		cyclone::Vector3(20, 5, 5), // max velocity
		0.2 // damping
	);

	rules[4].init(1);
	rules[4].setParameters(
		5, // type
		0.5f, 1.0f, // age range
		cyclone::Vector3(-20, 2, -5), // min velocity
		cyclone::Vector3(20, 18, 5), // max velocity
		0.01 // damping
	);
	rules[4].payloads[0].set(3, 5);

	rules[5].init(0);
	rules[5].setParameters(
		6, // type
		3, 5, // age range
		cyclone::Vector3(-5, 5, -5), // min velocity
		cyclone::Vector3(5, 10, 5), // max velocity
		0.95 // damping
	);

	rules[6].init(1);
	rules[6].setParameters(
		7, // type
		4, 5, // age range
		cyclone::Vector3(-5, 50, -5), // min velocity
		cyclone::Vector3(5, 60, 5), // max velocity
		0.01 // damping
	);
	rules[6].payloads[0].set(8, 10);

	rules[7].init(0);
	rules[7].setParameters(
		8, // type
		0.25f, 0.5f, // age range
		cyclone::Vector3(-1, -1, -1), // min velocity
		cyclone::Vector3(1, 1, 1), // max velocity
		0.01 // damping
	);

	rules[8].init(0);
	rules[8].setParameters(
		9, // type
		3, 5, // age range
		cyclone::Vector3(-15, 10, -5), // min velocity
		cyclone::Vector3(15, 15, 5), // max velocity
		0.95 // damping
	);
	// ... and so on for other firework types ...
	rules[9].init(1);
	rules[9].setParameters(
		10, // type
		0.3, 3, // age range
		cyclone::Vector3(-5, 5, -5), // min velocity
		cyclone::Vector3(5, 10, 5), // max velocity
		0.05 // damping
	);
	rules[9].payloads[0].set(1, 100);
}

void FireworksDemo::initGraphics()
{
	// Call the superclass
	Application::initGraphics();

	// But override the clear color
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

const char* FireworksDemo::getTitle()
{
	return "Cyclone > Fireworks Demo";
}

void FireworksDemo::create(unsigned type, const Firework* parent)
{
	// Get the rule needed to create this firework
	FireworkRule* rule = rules + (type - 1);

	// Create the firework
	rule->create(fireworks + nextFirework, parent);

	// Increment the index for the next firework
	nextFirework = (nextFirework + 1) % maxFireworks;
}

void FireworksDemo::create(unsigned type, unsigned number, const Firework* parent)
{
	for (unsigned i = 0; i < number; i++)
	{
		create(type, parent);
	}
}

void FireworksDemo::update()
{
	// Find the duration of the last frame in seconds
	float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
	if (duration <= 0.0f) return;

	for (Firework* firework = fireworks;
		firework < fireworks + maxFireworks;
		firework++)
	{
		// Check if we need to process this firework.
		if (firework->type > 0)
		{
			// Does it need removing?
			if (firework->update(duration))
			{
				// Find the appropriate rule
				FireworkRule* rule = rules + (firework->type - 1);

				// Delete the current firework (this doesn't affect its
				// position and velocity for passing to the create function,
				// just whether or not it is processed for rendering or
				// physics.
				firework->type = 0;

				// Add the payload
				for (unsigned i = 0; i < rule->payloadCount; i++)
				{
					Payload* payload = rule->payloads + i;
					create(payload->type, payload->count, firework);
				}
			}
		}
	}

	Application::update();
}

void FireworksDemo::display()
{
	const static double size = 0.1f;

	// Clear the viewport and set the camera direction
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 4.0, 10.0, 0.0, 4.0, 0.0, 0.0, 1.0, 0.0);

	// Render each firework in turn
	glBegin(GL_QUADS);
	for (Firework* firework = fireworks;
		firework < fireworks + maxFireworks;
		firework++)
	{
		// Check if we need to process this firework.
		if (firework->type > 0)
		{
			switch (firework->type)
			{
			case 1: glColor3f(1, 0, 0); break;
			case 2: glColor3f(1, 0.5f, 0); break;
			case 3: glColor3f(1, 1, 0); break;
			case 4: glColor3f(0, 1, 0); break;
			case 5: glColor3f(0, 1, 1); break;
			case 6: glColor3f(0.4f, 0.4f, 1); break;
			case 7: glColor3f(1, 0, 1); break;
			case 8: glColor3f(1, 1, 1); break;
			case 9: glColor3f(1, 0.5f, 0.5f); break;
			case 10: glColor3f(1, 0.9f, 0.f); break;
			};

			const cyclone::Vector3& pos = firework->getPosition();
			glVertex3f(pos.x - size, pos.y - size, pos.z);
			glVertex3f(pos.x + size, pos.y - size, pos.z);
			glVertex3f(pos.x + size, pos.y + size, pos.z);
			glVertex3f(pos.x - size, pos.y + size, pos.z);

			// Render the firework's reflection
			glVertex3f(pos.x - size, -pos.y - size, pos.z);
			glVertex3f(pos.x + size, -pos.y - size, pos.z);
			glVertex3f(pos.x + size, -pos.y + size, pos.z);
			glVertex3f(pos.x - size, -pos.y + size, pos.z);
		}
	}
	glEnd();
}

void FireworksDemo::key(unsigned char key)
{
	switch (key)
	{
	case '1': create(1, 1, NULL); break;
	case '2': create(2, 1, NULL); break;
	case '3': create(3, 1, NULL); break;
	case '4': create(4, 1, NULL); break;
	case '5': create(5, 1, NULL); break;
	case '6': create(6, 1, NULL); break;
	case '7': create(7, 1, NULL); break;
	case '8': create(8, 1, NULL); break;
	case '9': create(9, 1, NULL); break;
	case '0': create(10, 1, NULL); break;
	default: Application::key(key);
	}
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
	return new FireworksDemo();
}
