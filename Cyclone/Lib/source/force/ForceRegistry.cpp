#include "cyclone/force/ForceRegistry.h"
#include "cyclone/force/ForceGenerator.h"

using namespace cyclone;

void ForceRegistry::updateForces(double duration)
{
	Registry::iterator i = registrations.begin();
	for (; i != registrations.end(); i++)
	{
		i->fg->updateForce(i->body, duration);
	}
}

void ForceRegistry::add(RigidBody* body, ForceGenerator* fg)
{
	ForceRegistry::ForceRegistration registration;
	registration.body = body;
	registration.fg = fg;
	registrations.push_back(registration);
}