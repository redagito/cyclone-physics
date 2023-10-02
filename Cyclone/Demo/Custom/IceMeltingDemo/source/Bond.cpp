#include "Bond.h"

#include <GL/freeglut.h>

#include "Molecule.h"

void Bond::update(double duration)
{
	auto m0 = dynamic_cast<Molecule*>(particle[0]);
	if (m0 == nullptr)
	{
		// Not a molecule
		return;
	}

	auto m1 = dynamic_cast<Molecule*>(particle[1]);
	if (m1 == nullptr)
	{
		// Not a molecule
		return;
	}

	// average the temperatures of the bonded molecules to get bond temperature
	temp = (m0->getTemp() + m1->getTemp()) / 2;

	if (m1->getPosition().y > m0->getPosition().y)
	{
		m1->setTemp(m1->getTemp() + (temp * conductivity));
	}
	else
	{
		m0->setTemp(m0->getTemp() + (temp * conductivity));
	}

	// checks to see if this link should be destroyed
	if (temp > 0.9f) state = 0;
}

void Bond::draw()
{
	const cyclone::Vector3& p0 = particle[0]->getPosition();
	const cyclone::Vector3& p1 = particle[1]->getPosition();

	glBegin(GL_LINES);
	glColor3f(temp, 0, 0); // gets more red depending on temperature of connected molecules
	glVertex3f(p0.x, p0.y, p0.z);
	glVertex3f(p1.x, p1.y, p1.z);
	glEnd();
}

const double Bond::getConductivity() const
{
	return conductivity;
}

const double Bond::getTemp() const
{
	return temp;
}

const unsigned Bond::getState() const
{
	return state;
}

void Bond::setConductivity(double c)
{
	conductivity = c;
}

void Bond::setTemp(double t)
{
	if (t <= 1) temp = t;
}

void Bond::setState(unsigned s)
{
	if (s == 1 || s == 0) state = s;
}