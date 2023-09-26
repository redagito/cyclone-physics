#include "cyclone/force/Explosion.h"
#include "cyclone/RigidBody.h"

using namespace cyclone;

void Explosion::updateTimePassed(double duration)
{
	timePassed += duration;
}

void Explosion::reset()
{
	timePassed = 0.0;
}

void Explosion::updateForce(RigidBody* body, double duration)
{
	if (timePassed <= implosionDuration)
	{
		// Implosion, force towards point of explosion
		auto direction = detonation - body->getPosition();
		auto distance = direction.magnitude();
		if (distance <= implosionMaxRadius && distance > implosionMinRadius)
		{
			// Apply implosion force
			auto force = direction.normalise() * implosionForce;;
			body->addForce(force * duration);
		}
	}
	else if (timePassed <= concussionDuration + implosionDuration)
	{
		// Shockwave away from point of explosion
		auto direction = body->getPosition() - detonation;
		body->addForce(direction * peakConcussionForce * duration);
	}
	else if (timePassed <= convectionDuration + concussionDuration + implosionDuration)
	{
		// Chimney
	}
}

void Explosion::updateForce(Particle* /*particle*/, double /*duration*/)
{
	// TODO
}