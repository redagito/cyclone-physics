#pragma once

#include <cyclone/Cyclone.h>

struct Payload;
class Firework;

/**
 * Firework rules control the length of a firework's fuse and the
 * particles it should evolve into.
 */
struct FireworkRule
{
	/** The type of firework that is managed by this rule. */
	unsigned type = 0;

	/** The minimum length of the fuse. */
	double minAge = 0.f;

	/** The maximum legnth of the fuse. */
	double maxAge = 0.f;

	/** The minimum relative velocity of this firework. */
	cyclone::Vector3 minVelocity;

	/** The maximum relative velocity of this firework. */
	cyclone::Vector3 maxVelocity;

	/** The damping of this firework type. */
	double damping = 0.f;

	/** The number of payloads for this firework type. */
	unsigned payloadCount;

	/** The set of payloads. */
	Payload* payloads = nullptr;

	FireworkRule();

	void init(unsigned payloadCount);

	~FireworkRule();

	/**
	 * Set all the rule parameters in one go.
	 */
	void setParameters(unsigned type, double minAge, double maxAge,
		const cyclone::Vector3& minVelocity, const cyclone::Vector3& maxVelocity,
		double damping);

	/**
	 * Creates a new firework of this type and writes it into the given
	 * instance. The optional parent firework is used to base position
	 * and velocity on.
	 */
	void create(Firework* firework, const Firework* parent = NULL) const;
};