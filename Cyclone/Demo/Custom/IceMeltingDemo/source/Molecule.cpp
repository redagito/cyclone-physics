#include "Molecule.h"

#include <GL/freeglut.h>

void Molecule::update(double duration)
{
	if (getPosition().y < 0.1f) temp += duration / (rand() % 30 + 15);

	if (temp >= 1) state = 1;
}

void Molecule::draw()
{
	cyclone::Vector3 pos = getPosition();

	glColor3f(temp, 0, 0);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glutSolidSphere(size, 20, 10);
	glPopMatrix();
}

const double Molecule::getSize() const
{
	return size;
}

const double Molecule::getTemp() const
{
	return temp;
}

const unsigned Molecule::getState() const
{
	return state;
}

void Molecule::setSize(double s)
{
	size = s;
}

void Molecule::setTemp(double t)
{
	if (t <= 1) temp = t;
}

void Molecule::setState(unsigned s)
{
	if (s == 1 || s == 0) state = s;
}