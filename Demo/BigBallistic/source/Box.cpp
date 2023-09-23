#include "Box.h"

#include <GL/freeglut.h>

Box::Box()
{
	body = new cyclone::RigidBody;
}

Box::~Box()
{
	delete body;
}

/** Draws the box, excluding its shadow. */
void Box::render()
{
	// Get the OpenGL transformation
	GLfloat mat[16];
	body->getGLTransform(mat);

	glPushMatrix();
	glMultMatrixf(mat);
	glScalef(halfSize.x * 2, halfSize.y * 2, halfSize.z * 2);
	glutSolidCube(1.0f);
	glPopMatrix();
}

/** Sets the box to a specific location. */
void Box::setState(double z)
{
	body->setPosition(0, 3, z);
	body->setOrientation(1, 0, 0, 0);
	body->setVelocity(0, 0, 0);
	body->setRotation(cyclone::Vector3(0, 0, 0));
	halfSize = cyclone::Vector3(1, 1, 1);

	double mass = halfSize.x * halfSize.y * halfSize.z * 8.0f;
	body->setMass(mass);

	cyclone::Matrix3 tensor;
	tensor.setBlockInertiaTensor(halfSize, mass);
	body->setInertiaTensor(tensor);

	body->setLinearDamping(0.95f);
	body->setAngularDamping(0.8f);
	body->clearAccumulators();
	body->setAcceleration(0, -10.0f, 0);

	body->setCanSleep(false);
	body->setAwake();

	body->calculateDerivedData();
	calculateInternals();
}