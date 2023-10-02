#pragma once

#include <cyclonedemo/Application.h>
#include <cyclonedemo/Timing.h>

#include <algorithm>

#include "Molecule.h"
#include "Bond.h"

class IceMeltingDemo : public Application
{
private:
	cyclone::ParticleWorld world;
	cyclone::GroundContacts groundContactGenerator;
	Molecule* molecules = nullptr;
	Bond* bonds = nullptr;

	const unsigned cubeDepth = 0;
	const unsigned bondCount = 0;
	const unsigned moleculeCount = 0;

	cyclone::ParticleWorld::ContactGenerators origContactGenerators;
	Molecule* moleculesOrig = nullptr;
	Bond* bondsOrig = nullptr;
	bool spaceFlag = false;

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