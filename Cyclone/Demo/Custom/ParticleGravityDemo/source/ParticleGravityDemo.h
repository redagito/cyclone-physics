#pragma once

#include <cyclonedemo/MassAggregateApplication.h>

class ParticleGravityDemo : public MassAggregateApplication
{
private:
	cyclone::ParticleGravity gravity;

public:
	ParticleGravityDemo();
	~ParticleGravityDemo();

	virtual void initGraphics();

	virtual const char* getTitle();

	virtual void update();

	virtual void display();

	virtual void key(unsigned char key);
};