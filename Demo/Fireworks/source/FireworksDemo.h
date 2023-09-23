#pragma once

#include <cyclonedemo/Application.h>

#include "Firework.h"
#include "FireworkRule.h"

/**
 * The main demo class definition.
 */
class FireworksDemo : public Application
{
	/**
	 * Holds the maximum number of fireworks that can be in use.
	 */
	const static unsigned maxFireworks = 1024;

	/** Holds the firework data. */
	Firework fireworks[maxFireworks];

	/** Holds the index of the next firework slot to use. */
	unsigned nextFirework;

	/** And the number of rules. */
	const static unsigned ruleCount = 11;

	/** Holds the set of rules. */
	FireworkRule rules[ruleCount];

	/** Dispatches a firework from the origin. */
	void create(unsigned type, const Firework* parent = NULL);

	/** Dispatches the given number of fireworks from the given parent. */
	void create(unsigned type, unsigned number, const Firework* parent);

	/** Creates the rules. */
	void initFireworkRules();

public:
	/** Creates a new demo object. */
	FireworksDemo();
	~FireworksDemo();

	/** Sets up the graphic rendering. */
	virtual void initGraphics();

	/** Returns the window title for the demo. */
	virtual const char* getTitle();

	/** Update the particle positions. */
	virtual void update();

	/** Display the particle positions. */
	virtual void display();

	/** Handle a keypress. */
	virtual void key(unsigned char key);
};