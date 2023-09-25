#pragma once

#include <vector>


namespace cyclone
{
	class ForceGenerator;
	class RigidBody;

	/**
	* Holds all the force generators and the bodies they apply to.
	*/
	class ForceRegistry
	{
	protected:

		/**
		* Keeps track of one force generator and the body it
		* applies to.
		*/
		struct ForceRegistration
		{
			RigidBody* body = nullptr;
			ForceGenerator* fg = nullptr;
		};

		/**
		* Holds the list of registrations.
		*/
		typedef std::vector<ForceRegistration> Registry;
		Registry registrations;

	public:
		/**
		* Registers the given force generator to apply to the
		* given body.
		*/
		void add(RigidBody* body, ForceGenerator* fg);

		/**
		* Removes the given registered pair from the registry.
		* If the pair is not registered, this method will have
		* no effect.
		*/
		void remove(RigidBody* body, ForceGenerator* fg);

		/**
		* Clears all registrations from the registry. This will
		* not delete the bodies or the force generators
		* themselves, just the records of their connection.
		*/
		void clear();

		/**
		* Calls all the force generators to update the forces of
		* their corresponding bodies.
		*/
		void updateForces(double duration);
	};
}