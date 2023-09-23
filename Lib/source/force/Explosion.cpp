#include "cyclone/force/Explosion.h"
#include "cyclone/RigidBody.h"

using namespace cyclone;

void Explosion::updateForce(RigidBody* body, double duration)
{
	timePassed += duration;

	if (timePassed <= implosionDuration)
	{
		// Implosion, force towards point of explosion
		auto direction = body->getPosition() - detonation;
		auto distance = direction.magnitude();
		if (distance <= implosionMaxRadius && distance > implosionMinRadius)
		{
			// Apply implosion force
			auto force = direction.normalise() * implosionForce;;
			body->addForce(force);
		}
	}
	else if (timePassed <= concussionDuration)
	{
		// Shockwave
	}
	else if (timePassed <= convectionDuration)
	{
		// Chimney
	}
}

void Explosion::updateForce(Particle* /*particle*/, double /*duration*/)
{
	// TODO
}