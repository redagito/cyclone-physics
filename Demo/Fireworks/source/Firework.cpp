#include "Firework.h"

bool Firework::update(double duration)
{
	// Update our physical state
	integrate(duration);

	// We work backwards from our age to zero.
	age -= duration;
	return (age < 0.0) || (position.y < 0.0);
}
