#pragma once

#include <cyclonedemo/RigidBodyApplication.h>

#include "Block.h"

#define MAX_BLOCKS 9

/**
 * The main demo class definition.
 */
class FractureDemo : public RigidBodyApplication
{
	/** Tracks if a block has been hit. */
	bool hit;
	bool ball_active;
	unsigned fracture_contact;

	/** Handle random numbers. */
	cyclone::Random random;

	/** Holds the bodies. */
	Block blocks[MAX_BLOCKS];

	/** Holds the projectile. */
	cyclone::CollisionSphere ball;

	/** Processes the contact generation code. */
	virtual void generateContacts();

	/** Processes the objects in the simulation forward in time. */
	virtual void updateObjects(double duration);

	/** Resets the position of all the blocks. */
	virtual void reset();

	/** Processes the physics. */
	virtual void update();

public:
	/** Creates a new demo object. */
	FractureDemo();

	/** Returns the window title for the demo. */
	virtual const char* getTitle();

	/** Display the particle positions. */
	virtual void display();
};