#pragma once

#include <cyclone/Cyclone.h>

class Bond : public cyclone::ParticleRod
{
	double conductivity = 0.0;
	double temp = 0.0;
	// if 0, the world should delete this and remove any references to it
	unsigned int state = 0;

public:
	// Constructors:

	Bond() : conductivity(0.001), temp(0.0), state(1) {}
	~Bond() = default;

	void update(double duration);
	void draw();

	const double getConductivity() const;
	const double getTemp() const;
	const unsigned getState() const;

	void setConductivity(double c);
	void setTemp(double t);
	void setState(unsigned s);
};