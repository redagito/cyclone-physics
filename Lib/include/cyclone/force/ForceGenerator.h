#pragma once


/*
 * Interface file for the force generators.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

namespace cyclone
{
	class RigidBody;

	/**
	 * A force generator can be asked to add a force to one or more
	 * bodies.
	 */
	class ForceGenerator
	{
	public:
		virtual ~ForceGenerator() = default;

		/**
		 * Overload this in implementations of the interface to calculate
		 * and update the force applied to the given rigid body.
		 */
		virtual void updateForce(RigidBody* body, double duration) = 0;
	};
}