#include "tornado/Particle.h"

#include "tornado/Configuration.h"

#include <algorithm>

using namespace tornado;

void Particle::integrate(float duration, const Configuration& config)
{
	// The velocity based on forces and particle mass
	// [m/s^2]
	auto acceleration =  m_force * (1.f / m_mass);

	// New velocity from old velocity and new acceleration
	// [m/s]
	m_velocity = m_velocity * config.defaultDamping + acceleration * duration;

	// Clamp velocity to max allowed speed
	auto speed = glm::length(m_velocity);
	if (speed > config.maxSpeed)
	{
		m_velocity = glm::normalize(m_velocity)* config.maxSpeed;
	}
	else if (speed < config.minSpeed)
	{
		// Below min speed
		m_velocity *= 0.f;
	}

	// New position assumes constant velocity in timestep
	// [m]
	m_position = m_position + m_velocity * duration;
}