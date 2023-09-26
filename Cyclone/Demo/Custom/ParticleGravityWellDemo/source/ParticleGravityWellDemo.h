#pragma once

#include <vector>

#include <cyclonedemo/MassAggregateApplication.h>

class ParticleGravityWellDemo : public MassAggregateApplication
{
private:
	std::vector<cyclone::ParticleGravityWell> gravityWells;

public:
	ParticleGravityWellDemo();

	virtual void initGraphics();

	virtual const char* getTitle();

	virtual void key(unsigned char key);
};