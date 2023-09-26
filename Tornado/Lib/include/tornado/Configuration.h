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
		double maxSpeed = 299790000.0;

		// Minimum achievable movement speed
		// Any speed below is set to 0
		// In [m/s]
		double minSpeed = 10.0e-20;

		// Minimum mass for any object
		// Any mass below is set to this value
		// [kg]
		// Default at 1 mg 
		double minMass = 1.0e-6;

		// The default damping value
		double defaultDamping = 0.9995;
	};
}