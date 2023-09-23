#include "cyclone/contact/ParticleLink.h"
#include "cyclone/Vector3.h"
#include "cyclone/Particle.h"

using namespace cyclone;

ParticleLink::ParticleLink()
{
	particle[0] = nullptr;
	particle[1] = nullptr;
}

double ParticleLink::currentLength() const
{
	Vector3 relativePos = particle[0]->getPosition() -
		particle[1]->getPosition();
	return relativePos.magnitude();
}