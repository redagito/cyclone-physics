#pragma once

#include <cyclone/Cyclone.h>

class Molecule : public cyclone::Particle
{
	double size = 0.09;
	double temp = 0.0;
	unsigned state = 1;

public:
	Molecule() = default;
	~Molecule() = default;

	void update(double duration);
	void draw();

	const double getSize() const;
	const double getTemp() const;
	const unsigned getState() const;

	void setSize(double s);
	void setTemp(double t);
	void setState(unsigned s);
};