#pragma once

#include <cyclonedemo/RigidBodyApplication.h>

#include "AmmoRound.h"
#include "Box.h"

/**
 * The main demo class definition.
 */
class BigBallisticDemo : public RigidBodyApplication
{
	/**
	 * Holds the maximum number of  rounds that can be
	 * fired.
	 */
	const static unsigned ammoRounds = 256;

	/** Holds the particle data. */
	AmmoRound ammo[ammoRounds];

	/**
	* Holds the number of boxes in the simulation.
	*/
	const static unsigned boxes = 1;

	/** Holds the box data. */
	Box boxData[boxes];

	/** Holds the current shot type. */
	ShotType currentShotType = ShotType::PISTOL;

	/** Resets the position of all the boxes and primes the explosion. */
	virtual void reset();

	/** Build the contacts for the current situation. */
	virtual void generateContacts();

	/** Processes the objects in the simulation forward in time. */
	virtual void updateObjects(double duration);

	/** Dispatches a round. */
	void fire();

public:
	/** Creates a new demo object. */
	BigBallisticDemo();

	/** Returns the window title for the demo. */
	virtual const char* getTitle();

	/** Sets up the rendering. */
	virtual void initGraphics();

	/** Display world. */
	virtual void display();

	/** Handle a mouse click. */
	virtual void mouse(int button, int state, int x, int y);

	/** Handle a keypress. */
	virtual void key(unsigned char key);
};