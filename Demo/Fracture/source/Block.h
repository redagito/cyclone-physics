#pragma once

#include <cyclone/Cyclone.h>

class Block : public cyclone::CollisionBox
{
public:
	bool exists = false;

	Block();

	~Block();

	/** Draws the block. */
	void render();

	/** Sets the block to a specific location. */
	void setState(const cyclone::Vector3& position,
		const cyclone::Quaternion& orientation,
		const cyclone::Vector3& extents,
		const cyclone::Vector3& velocity);

	/**
	 * Calculates and sets the mass and inertia tensor of this block,
	 * assuming it has the given constant density.
	 */
	void calculateMassProperties(double invDensity);

	/**
	 * Performs the division of the given block into four, writing the
	 * eight new blocks into the given blocks array. The blocks array can be
	 * a pointer to the same location as the target pointer: since the
	 * original block is always deleted, this effectively reuses its storage.
	 * The algorithm is structured to allow this reuse.
	 */
	void divideBlock(const cyclone::Contact& contact,
		Block* target, Block* blocks);
};