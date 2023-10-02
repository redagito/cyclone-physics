#pragma once

#include <cyclonedemo/Application.h>
#include <cyclonedemo/Timing.h>

#include <algorithm>

#include "Molecule.h"
#include "Bond.h"

class IceMeltingDemo : public Application
{
private:
	cyclone::ParticleWorld world_;
	cyclone::GroundContacts groundContactGenerator_;
	Molecule* molecules = nullptr;
	Bond* bonds = nullptr;

	const unsigned cubeDepth = 0;
	const unsigned bondCount = 0;
	const unsigned moleculeCount = 0;

	// variables used for reseting the cube
	cyclone::ParticleWorld::ContactGenerators origContactGenerators;
	Molecule* moleculesOrig = nullptr;
	Bond* bondsOrig = nullptr;
	bool spaceFlag = false;

	// variables for changing duration
	float duration = 0.f;
	float forcedDuration = 0.f;
	bool zeroFlag = false;

public:
	IceMeltingDemo(const unsigned depth);
	virtual ~IceMeltingDemo();
	
	virtual void initGraphics();
	virtual void update();
	virtual void display();
	virtual void key(unsigned char key);
	virtual const char* getTitle();
};