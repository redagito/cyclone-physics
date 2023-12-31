#pragma once

#include <glm/glm.hpp>

namespace tornado
{
	class Configuration;

	class Particle
	{
	public:

		// 
		void integrate(float duration, const Configuration& config);

	private:
		// Current position in world space
		// In [m]
		glm::vec3 m_position;

		// Current velocity in world space
		// In [m/s]
		glm::vec3 m_velocity;

		// Mass
		// In [kg]
		float m_mass = 0.1f;

		// Sets the mass to be infinite
		// If true, the particle is not affected by any forces
		// This overrides the particle mass setting
		bool m_hasInfiniteMass = false;

		// Accumulated force vectors affecting this particle since last update
		// In Newton, [kg*m/s^2]
		glm::vec3 m_force;
	};
}