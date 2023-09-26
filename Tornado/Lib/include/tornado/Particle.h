#pragma once

#include <glm/glm.hpp>

namespace tornado
{
	class Particle
	{
	public:

		// 
		void integrate(float duration);

	private:
		// Current position in world space
		// Units are [m]
		glm::vec3 m_position;

		// Current velocity in world space
		// In [m/s]
		glm::vec3 m_velocity;

		// Mass in [kg]
		double m_mass = 0.1;
	};
}