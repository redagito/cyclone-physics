#pragma once

#include <cyclonedemo/Application.h>
#include <cyclone/Cyclone.h>

#include "Platform.h"
#include "BlobForceGenerator.h"

/**
 * The main demo class definition.
 */
class BlobDemo : public Application
{
	cyclone::Particle* blobs = nullptr;

	Platform* platforms = nullptr;

	cyclone::ParticleWorld world;

	BlobForceGenerator blobForceGenerator;

	/* The control for the x-axis. */
	float xAxis;

	/* The control for the y-axis. */
	float yAxis;

	void reset();

public:
	/** Creates a new demo object. */
	BlobDemo();
	virtual ~BlobDemo();

	/** Returns the window title for the demo. */
	virtual const char* getTitle();

	/** Display the particles. */
	virtual void display();

	/** Update the particle positions. */
	virtual void update();

	/** Handle a key press. */
	virtual void key(unsigned char key);

};