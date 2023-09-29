#pragma once

#include <cfloat>

namespace tornado
{
	// Configuration for the physics simulation
	// Max, min values, epsilon and hard restrictions to improve stability
	// Used for any object within the simulation
	class Configuration
	{
	public:
		// Maximum achievable movement speed
		// Any speed above is set to this value
		// In [m/s]
		// Capped at approximately light speed by default
		float maxSpeed = 299790000.f;

		// Minimum mass for any object
		// Any mass below is set to this value
		// In [kg]
		// Default at 1 mg 
		float minMass = 1.0e-6f;

		// The default damping value (friction)
		// No unit
		// TODO Usage
		float defaultDamping = 0.9995f;

		// The maximum timestep allowed for the physic simulation
		// Anything higher would affect simulation stability
		// In [s]
		// Default at 1/20 second
		float maxTimeStep = 0.05f;

		// The default timestep
		// In [s]
		// Default at 1/30 second (30 fps)
		float defaultTimeStep = 0.033333f;
	};
}