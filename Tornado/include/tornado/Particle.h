#pragma once

#include <glm/glm.hpp>

namespace tornado
{
	class Particle
	{
	public:
		glm::vec3 m_position;

		void integrate(float duration);
	};
}