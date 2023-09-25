#pragma once

#include <cyclonedemo/MassAggregateApplication.h>
#include <cyclone/Cyclone.h>

/**
 * The main demo class definition.
 */
class BridgeDemo : public MassAggregateApplication
{
	cyclone::ParticleCableConstraint* supports = nullptr;
	cyclone::ParticleCable* cables = nullptr;
	cyclone::ParticleRod* rods = nullptr;

	cyclone::Vector3 massPos;
	cyclone::Vector3 massDisplayPos;

	/**
	 * Updates particle masses to take into account the mass
	 * that's crossing the bridge.
	 */
	void updateAdditionalMass();

public:
	/** Creates a new demo object. */
	BridgeDemo();
	virtual ~BridgeDemo();

	/** Returns the window title for the demo. */
	virtual const char* getTitle();

	/** Display the particles. */
	virtual void display();

	/** Update the particle positions. */
	virtual void update();

	/** Handle a key press. */
	virtual void key(unsigned char key);
};