#include "cyclone/force/Aero.h"
#include "cyclone/RigidBody.h"

using namespace cyclone;

Aero::Aero(const Matrix3& tensor, const Vector3& position, const Vector3* windspeed)
{
	Aero::tensor = tensor;
	Aero::position = position;
	Aero::windspeed = windspeed;
}

void Aero::updateForce(RigidBody* body, double duration)
{
	Aero::updateForceFromTensor(body, duration, tensor);
}

void Aero::updateForceFromTensor(RigidBody* body, double /*duration*/,
	const Matrix3& tensr)
{
	// Calculate total velocity (windspeed and body's velocity).
	Vector3 velocity = body->getVelocity();
	velocity += *windspeed;

	// Calculate the velocity in body coordinates
	Vector3 bodyVel = body->getTransform().transformInverseDirection(velocity);

	// Calculate the force in body coordinates
	Vector3 bodyForce = tensr.transform(bodyVel);
	Vector3 force = body->getTransform().transformDirection(bodyForce);

	// Apply the force
	body->addForceAtBodyPoint(force, position);
}