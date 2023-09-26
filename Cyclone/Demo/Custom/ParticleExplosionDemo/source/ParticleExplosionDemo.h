#pragma once

#include <vector>

#include <cyclonedemo/MassAggregateApplication.h>

class ParticleExplosionDemo : public MassAggregateApplication
{
private:
	std::vector<cyclone::Explosion> explosions;

	bool fired = false;

	void reset();
	void fire();

public:
	ParticleExplosionDemo();

	virtual void initGraphics();

	virtual const char* getTitle();

	virtual void updateObjects(double duration);

	virtual void key(unsigned char key);
};