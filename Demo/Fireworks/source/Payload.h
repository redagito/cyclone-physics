#pragma once

/**
 * The payload is the new firework type to create when this
 * firework's fuse is over.
 */
struct Payload
{
	/** The type of the new particle to create. */
	unsigned type = 0;

	/** The number of particles in this payload. */
	unsigned count = 0;

	/** Sets the payload properties in one go. */
	void set(unsigned type, unsigned count);
};