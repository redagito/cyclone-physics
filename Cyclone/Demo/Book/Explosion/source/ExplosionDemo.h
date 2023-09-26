#pragma once

#include <cyclonedemo/RigidBodyApplication.h>

#include "Box.h"
#include "Ball.h"

/**
 * The main demo class definition.
 */
class ExplosionDemo : public RigidBodyApplication
{
	cyclone::Explosion explosion;
	bool fired = false;

	bool editMode, upMode;

	static constexpr unsigned int OBJECTS = 20;
	/**
	 * Holds the number of boxes in the simulation.
	 */
	const static unsigned boxes = OBJECTS;

	/** Holds the box data. */
	Box boxData[boxes];

	/**
	 * Holds the number of balls in the simulation.
	 */
	const static unsigned balls = OBJECTS;

	/** Holds the ball data. */
	Ball ballData[balls];

	/** Detonates the explosion. */
	void fire();

	/** Resets the position of all the boxes and primes the explosion. */
	virtual void reset();

	/** Processes the contact generation code. */
	virtual void generateContacts();

	/** Processes the objects in the simulation forward in time. */
	virtual void updateObjects(double duration);

public:
	/** Creates a new demo object. */
	ExplosionDemo();

	/** Sets up the rendering. */
	virtual void initGraphics();

	/** Returns the window title for the demo. */
	virtual const char* getTitle();

	/** Display the particle positions. */
	virtual void display();

	/** Handles a key press. */
	virtual void key(unsigned char key);

	/** Handle a mouse drag */
	virtual void mouseDrag(int x, int y);
};