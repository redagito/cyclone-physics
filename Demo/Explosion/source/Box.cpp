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

	if (isOverlapping) glColor3f(0.7f, 1.0f, 0.7f);
	else if (body->getAwake()) glColor3f(1.0f, 0.7f, 0.7f);
	else glColor3f(0.7f, 0.7f, 1.0f);

	glPushMatrix();
	glMultMatrixf(mat);
	glScalef(halfSize.x * 2, halfSize.y * 2, halfSize.z * 2);
	glutSolidCube(1.0f);
	glPopMatrix();
}

/** Draws the ground plane shadow for the box. */
void Box::renderShadow()
{
	// Get the OpenGL transformation
	GLfloat mat[16];
	body->getGLTransform(mat);

	glPushMatrix();
	glScalef(1.0f, 0, 1.0f);
	glMultMatrixf(mat);
	glScalef(halfSize.x * 2, halfSize.y * 2, halfSize.z * 2);
	glutSolidCube(1.0f);
	glPopMatrix();
}

/** Sets the box to a specific location. */
void Box::setState(const cyclone::Vector3& position,
	const cyclone::Quaternion& orientation,
	const cyclone::Vector3& extents,
	const cyclone::Vector3& velocity)
{
	body->setPosition(position);
	body->setOrientation(orientation);
	body->setVelocity(velocity);
	body->setRotation(cyclone::Vector3(0, 0, 0));
	halfSize = extents;

	double mass = halfSize.x * halfSize.y * halfSize.z * 8.0f;
	body->setMass(mass);

	cyclone::Matrix3 tensor;
	tensor.setBlockInertiaTensor(halfSize, mass);
	body->setInertiaTensor(tensor);

	body->setLinearDamping(0.95f);
	body->setAngularDamping(0.8f);
	body->clearAccumulators();
	body->setAcceleration(0, -10.0f, 0);

	body->setAwake();

	body->calculateDerivedData();
}

/** Positions the box at a random location. */
void Box::random(cyclone::Random* random)
{
	const static cyclone::Vector3 minPos(-5, 5, -5);
	const static cyclone::Vector3 maxPos(5, 10, 5);
	const static cyclone::Vector3 minSize(0.5f, 0.5f, 0.5f);
	const static cyclone::Vector3 maxSize(4.5f, 1.5f, 1.5f);

	setState(
		random->randomVector(minPos, maxPos),
		random->randomQuaternion(),
		random->randomVector(minSize, maxSize),
		cyclone::Vector3()
	);
}