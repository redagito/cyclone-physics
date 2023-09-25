#pragma once

namespace cyclone
{
	class Contact;

	/**
	 * A helper structure that contains information for the detector to use
	 * in building its contact data.
	 */
	class CollisionData
	{
	public:
		/**
		 * Holds the base of the collision data: the first contact
		 * in the array. This is used so that the contact pointer (below)
		 * can be incremented each time a contact is detected, while
		 * this pointer points to the first contact found.
		 * 
		 * Does not own the contactArray, global array managed and 
		 * provided by the app to have global contacts limit?
		 */
		Contact* contactArray = nullptr;

		/** Holds the contact array to write into. */
		Contact* contacts = nullptr;

		/** Holds the maximum number of contacts the array can take. */
		int contactsLeft = 0;

		/** Holds the number of contacts found so far. */
		unsigned contactCount = 0;

		/** Holds the friction value to write into any collisions. */
		double friction = 0.f;

		/** Holds the restitution value to write into any collisions. */
		double restitution = 0.f;

		/**
		 * Holds the collision tolerance, even uncolliding objects this
		 * close should have collisions generated.
		 */
		double tolerance = 0.f;

		/**
		 * Checks if there are more contacts available in the contact
		 * data.
		 */
		bool hasMoreContacts();

		/**
		 * Resets the data so that it has no used contacts recorded.
		 */
		void reset(unsigned maxContacts);

		/**
		 * Notifies the data that the given number of contacts have
		 * been added.
		 */
		void addContacts(unsigned count);
	};
}