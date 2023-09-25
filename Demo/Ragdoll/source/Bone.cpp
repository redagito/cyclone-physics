#include "Bone.h"

#include <GL/freeglut.h>

Bone::Bone()
{
	body = new cyclone::RigidBody();
}

Bone::~Bone()
{
	delete body;
}

/**
 * We use a sphere to collide bone on bone to allow some limited
 * interpenetration.
 */
cyclone::CollisionSphere Bone::getCollisionSphere() const
{
	cyclone::CollisionSphere sphere;
	sphere.body = body;
	sphere.radius = halfSize.x;
	sphere.offset = cyclone::Matrix4();
	if (halfSize.y < sphere.radius) sphere.radius = halfSize.y;
	if (halfSize.z < sphere.radius) sphere.radius = halfSize.z;
	sphere.calculateInternals();
	return sphere;
}

/** Draws the bone. */
void Bone::render()
{
	// Get the OpenGL transformation
	GLfloat mat[16];
	body->getGLTransform(mat);

	if (body->getAwake()) glColor3f(0.5f, 0.3f, 0.3f);
	else glColor3f(0.3f, 0.3f, 0.5f);

	glPushMatrix();
	glMultMatrixf(mat);
	glScalef(halfSize.x * 2, halfSize.y * 2, halfSize.z * 2);
	glutSolidCube(1.0f);
	glPopMatrix();
}

/** Sets the bone to a specific location. */
void Bone::setState(const cyclone::Vector3& position,
	const cyclone::Vector3& extents)
{
	body->setPosition(position);
	body->setOrientation(cyclone::Quaternion());
	body->setVelocity(cyclone::Vector3());
	body->setRotation(cyclone::Vector3());
	halfSize = extents;

	double mass = halfSize.x * halfSize.y * halfSize.z * 8.0f;
	body->setMass(mass);

	cyclone::Matrix3 tensor;
	tensor.setBlockInertiaTensor(halfSize, mass);
	body->setInertiaTensor(tensor);

	body->setLinearDamping(0.95f);
	body->setAngularDamping(0.8f);
	body->clearAccumulators();
	body->setAcceleration(cyclone::Vector3::GRAVITY);

	body->setCanSleep(false);
	body->setAwake();

	body->calculateDerivedData();
	calculateInternals();
}