#include "Payload.h"

/** Sets the payload properties in one go. */
void Payload::set(unsigned type, unsigned count)
{
	Payload::type = type;
	Payload::count = count;
}