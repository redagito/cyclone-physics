#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace tornado
{
	class Particle;

	class World
	{
	public:
		Particle* createParticle();

		void update(float duration);

	private:
		std::vector<Particle> m_particles;
	};
}