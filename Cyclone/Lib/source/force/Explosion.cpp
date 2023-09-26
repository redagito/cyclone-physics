#include "cyclone/force/Explosion.h"
#include "cyclone/RigidBody.h"
#include "cyclone/Particle.h"

#include <algorithm>

using namespace cyclone;

void Explosion::updateTimePassed(double duration)
{
	timePassed += duration;
}

void Explosion::reset()
{
	timePassed = 0.0;
}

Vector3  Explosion::getForce(const Vector3& position, double duration)
{
	if (timePassed <= implosionDuration)
	{
		// Implosion, force towards point of explosion
		auto direction = detonation - position;
		auto distance = direction.magnitude();
		if (distance <= implosionMaxRadius && distance > implosionMinRadius)
		{
			// Apply implosion force
			auto force = direction.normalise() * (implosionForce / (distance * distance));
			return force * duration;
		}
	}
	else if (timePassed <= concussionDuration + implosionDuration)
	{
		// Shockwave away from point of explosion
		auto direction = position - detonation;
		auto distance = direction.magnitude();

		// Check if is inside shockwave
		auto shockwaveTravelTime = timePassed - implosionDuration;
		// Average shockwave front where force is strongest
		auto shockwaveTravelDistance = shockwaveTravelTime * shockwaveSpeed;
		if (distance > shockwaveTravelDistance + shockwaveThickness || distance < shockwaveTravelDistance - shockwaveThickness)
		{
			// Outside of shockwave
			return Vector3{ 0.0 };
		}

		auto distanceToShockWavePeak = std::max(std::abs(shockwaveTravelDistance - distance), 1.0);
		// Gets proportional weaker with distance
		auto force = peakConcussionForce * duration / (distanceToShockWavePeak * distanceToShockWavePeak);
		return direction.normalise() * force;
	}
	else if (timePassed <= convectionDuration + concussionDuration + implosionDuration)
	{
		// Chimney
	}
	return Vector3{ 0.0 };
}

void Explosion::updateForce(RigidBody* body, double duration)
{
	body->addForce(getForce(body->getPosition(), duration));
}

void Explosion::updateForce(Particle* particle, double duration)
{
	particle->addForce(getForce(particle->getPosition(), duration));
}