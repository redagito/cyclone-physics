#pragma once

#include <cyclonedemo/Application.h>

#include "AmmoRound.h"

/*
 * The ballistic demo.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

 /**
  * The main demo class definition.
  */
class BallisticDemo : public Application
{
	/**
	 * Holds the maximum number of  rounds that can be
	 * fired.
	 */
	const static unsigned ammoRounds = 16;

	/** Holds the particle data. */
	AmmoRound ammo[ammoRounds];

	/** Holds the current shot type. */
	ShotType currentShotType = ShotType::PISTOL;

	/** Dispatches a round. */
	void fire();

public:
	/** Creates a new demo object. */
	BallisticDemo();

	/** Returns the window title for the demo. */
	virtual const char* getTitle();

	/** Update the particle positions. */
	virtual void update();

	/** Display the particle positions. */
	virtual void display();

	/** Handle a mouse click. */
	virtual void mouse(int button, int state, int x, int y);

	/** Handle a keypress. */
	virtual void key(unsigned char key);
};