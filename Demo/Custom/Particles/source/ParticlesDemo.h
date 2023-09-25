#pragma once

#include <cyclonedemo/MassAggregateApplication.h>

class ParticlesDemo : public MassAggregateApplication
{
private:
	cyclone::ParticleGravity gravity;

public:
	ParticlesDemo();
	~ParticlesDemo();

	virtual void initGraphics();

	virtual const char* getTitle();

	virtual void update();

	virtual void display();

	virtual void key(unsigned char key);
};