#include "Ball.h"

#include <GL/freeglut.h>

Ball::Ball()
{
	body = new cyclone::RigidBody;
}

Ball::~Ball()
{
	delete body;
}

/** Draws the box, excluding its shadow. */
void Ball::render()
{
	// Get the OpenGL transformation
	GLfloat mat[16];
	body->getGLTransform(mat);

	if (body->getAwake()) glColor3f(1.0f, 0.7f, 0.7f);
	else glColor3f(0.7f, 0.7f, 1.0f);

	glPushMatrix();
	glMultMatrixf(mat);
	glutSolidSphere(radius, 20, 20);
	glPopMatrix();
}

/** Draws the ground plane shadow for the box. */
void Ball::renderShadow()
{
	// Get the OpenGL transformation
	GLfloat mat[16];
	body->getGLTransform(mat);

	glPushMatrix();
	glScalef(1.0f, 0, 1.0f);
	glMultMatrixf(mat);
	glutSolidSphere(radius, 20, 20);
	glPopMatrix();
}

/** Sets the box to a specific location. */
void Ball::setState(cyclone::Vector3 position,
	cyclone::Quaternion orientation,
	double radius,
	cyclone::Vector3 velocity)
{
	body->setPosition(position);
	body->setOrientation(orientation);
	body->setVelocity(velocity);
	body->setRotation(cyclone::Vector3(0, 0, 0));
	Ball::radius = radius;

	double mass = 4.0f * 0.3333f * 3.1415f * radius * radius * radius;
	body->setMass(mass);

	cyclone::Matrix3 tensor;
	double coeff = 0.4f * mass * radius * radius;
	tensor.setInertiaTensorCoeffs(coeff, coeff, coeff);
	body->setInertiaTensor(tensor);

	body->setLinearDamping(0.95f);
	body->setAngularDamping(0.8f);
	body->clearAccumulators();
	body->setAcceleration(0, -10.0f, 0);

	//body->setCanSleep(false);
	body->setAwake();

	body->calculateDerivedData();
}

/** Positions the box at a random location. */
void Ball::random(cyclone::Random* random)
{
	const static cyclone::Vector3 minPos(-5, 5, -5);
	const static cyclone::Vector3 maxPos(5, 10, 5);
	cyclone::Random r;
	setState(
		random->randomVector(minPos, maxPos),
		random->randomQuaternion(),
		random->randomReal(0.5f, 1.5f),
		cyclone::Vector3()
	);
}