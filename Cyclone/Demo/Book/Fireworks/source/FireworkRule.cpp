#include "FireworkRule.h"

#include "Firework.h"
#include "Payload.h"

static cyclone::Random crandom;

FireworkRule::FireworkRule()
	:
	payloadCount(0),
	payloads(NULL)
{
}

void FireworkRule::init(unsigned payloadCount)
{
	FireworkRule::payloadCount = payloadCount;
	payloads = new Payload[payloadCount];
}

FireworkRule::~FireworkRule()
{
	if (payloads != NULL) delete[] payloads;
}

void FireworkRule::setParameters(unsigned type, double minAge, double maxAge,
	const cyclone::Vector3& minVelocity, const cyclone::Vector3& maxVelocity,
	double damping)
{
	FireworkRule::type = type;
	FireworkRule::minAge = minAge;
	FireworkRule::maxAge = maxAge;
	FireworkRule::minVelocity = minVelocity;
	FireworkRule::maxVelocity = maxVelocity;
	FireworkRule::damping = damping;
}

void FireworkRule::create(Firework* firework, const Firework* parent) const
{
	firework->type = type;
	firework->age = crandom.randomReal(minAge, maxAge);

	cyclone::Vector3 vel;
	if (parent) {
		// The position and velocity are based on the parent.
		firework->setPosition(parent->getPosition());
		vel += parent->getVelocity();
	}
	else
	{
		cyclone::Vector3 start;
		int x = (int)crandom.randomInt(3) - 1;
		start.x = 5.0f * double(x);
		firework->setPosition(start);
	}

	vel += crandom.randomVector(minVelocity, maxVelocity);
	firework->setVelocity(vel);

	// We use a mass of one in all cases (no point having fireworks
	// with different masses, since they are only under the influence
	// of gravity).
	firework->setMass(1);

	firework->setDamping(damping);

	firework->setAcceleration(cyclone::Vector3::GRAVITY);

	firework->clearAccumulator();
}