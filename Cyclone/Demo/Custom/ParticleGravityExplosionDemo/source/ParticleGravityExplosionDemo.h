#pragma once

#include <vector>

#include <cyclonedemo/MassAggregateApplication.h>

class ParticleGravityExplosionDemo : public MassAggregateApplication
{
private:
	std::vector<cyclone::Explosion> explosions;
	cyclone::ParticleGravity gravity;

	bool fired = false;

	void reset();
	void fire();

public:
	ParticleGravityExplosionDemo();

	virtual void initGraphics();

	virtual const char* getTitle();

	virtual void updateObjects(double duration);

	virtual void key(unsigned char key);
};