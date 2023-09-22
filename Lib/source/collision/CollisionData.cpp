#include "cyclone/collision/CollisionData.h"
#include "cyclone/contact/Contact.h"

using namespace cyclone;

/**
 * Checks if there are more contacts available in the contact
 * data.
 */
bool CollisionData::hasMoreContacts()
{
	return contactsLeft > 0;
}

/**
 * Resets the data so that it has no used contacts recorded.
 */
void CollisionData::reset(unsigned maxContacts)
{
	contactsLeft = maxContacts;
	contactCount = 0;
	contacts = contactArray;
}

/**
 * Notifies the data that the given number of contacts have
 * been added.
 */
void CollisionData::addContacts(unsigned count)
{
	// Reduce the number of contacts remaining, add number used
	contactsLeft -= count;
	contactCount += count;

	// Move the array forward
	contacts += count;
}