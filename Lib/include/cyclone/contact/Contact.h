#pragma once

#include "cyclone/Vector3.h"
#include "cyclone/Matrix3.h"

namespace cyclone
{
	/**
	 * @file
	 *
	 * This file contains the contact resolution system for cyclone,
	 * although it is called the contact resolution system, it handles
	 * collisions, contacts (sliding and resting), and constraints (such
	 * as joints).
	 *
	 * The resolver uses an iterative satisfaction algorithm; it loops
	 * through each contact and tries to resolve it. This is a very fast
	 * algorithm but can be unstable when the contacts are highly
	 * inter-related.
	 */
	class RigidBody;

	/**
	 * A contact represents two bodies in contact. Resolving a
	 * contact removes their interpenetration, and applies sufficient
	 * impulse to keep them apart. Colliding bodies may also rebound.
	 * Contacts can be used to represent positional joints, by making
	 * the contact constraint keep the bodies in their correct
	 * orientation.
	 *
	 * It can be a good idea to create a contact object even when the
	 * contact isn't violated. Because resolving one contact can violate
	 * another, contacts that are close to being violated should be
	 * sent to the resolver; that way if one resolution moves the body,
	 * the contact may be violated, and can be resolved. If the contact
	 * is not violated, it will not be resolved, so you only loose a
	 * small amount of execution time.
	 *
	 * The contact has no callable functions, it just holds the contact
	 * details. To resolve a set of contacts, use the contact resolver
	 * class.
	 */
	class Contact
	{
		// ... Other data as before ...

		/**
		 * The contact resolver object needs access into the contacts to
		 * set and effect the contact.
		 */
		friend class ContactResolver;

	public:
		/**
		 * Holds the bodies that are involved in the contact. The
		 * second of these can be NULL, for contacts with the scenery.
		 */
		RigidBody* body[2];

		/**
		 * Holds the lateral friction coefficient at the contact.
		 */
		double friction = 0.f;

		/**
		 * Holds the normal restitution coefficient at the contact.
		 */
		double restitution = 0.f;

		/**
		 * Holds the position of the contact in world coordinates.
		 */
		Vector3 contactPoint;

		/**
		 * Holds the direction of the contact in world coordinates.
		 */
		Vector3 contactNormal;

		/**
		 * Holds the depth of penetration at the contact point. If both
		 * bodies are specified then the contact point should be midway
		 * between the inter-penetrating points.
		 */
		double penetration = 0.f;

		/**
		 * Sets the data that doesn't normally depend on the position
		 * of the contact (i.e. the bodies, and their material properties).
		 */
		void setBodyData(RigidBody* one, RigidBody* two,
			double friction, double restitution);

	protected:

		/**
		 * A transform matrix that converts co-ordinates in the contact's
		 * frame of reference to world co-ordinates. The columns of this
		 * matrix form an orthonormal set of vectors.
		 */
		Matrix3 contactToWorld;

		/**
		 * Holds the closing velocity at the point of contact. This is set
		 * when the calculateInternals function is run.
		 */
		Vector3 contactVelocity;

		/**
		 * Holds the required change in velocity for this contact to be
		 * resolved.
		 */
		double desiredDeltaVelocity = 0.f;

		/**
		 * Holds the world space position of the contact point relative to
		 * centre of each body. This is set when the calculateInternals
		 * function is run.
		 */
		Vector3 relativeContactPosition[2];

	protected:
		/**
		 * Calculates internal data from state data. This is called before
		 * the resolution algorithm tries to do any resolution. It should
		 * never need to be called manually.
		 */
		void calculateInternals(double duration);

		/**
		 * Reverses the contact. This involves swapping the two rigid bodies
		 * and reversing the contact normal. The internal values should then
		 * be recalculated using calculateInternals (this is not done
		 * automatically).
		 */
		void swapBodies();

		/**
		 * Updates the awake state of rigid bodies that are taking
		 * place in the given contact. A body will be made awake if it
		 * is in contact with a body that is awake.
		 */
		void matchAwakeState();

		/**
		 * Calculates and sets the internal value for the desired delta
		 * velocity.
		 */
		void calculateDesiredDeltaVelocity(double duration);

		/**
		 * Calculates and returns the velocity of the contact
		 * point on the given body.
		 */
		Vector3 calculateLocalVelocity(unsigned bodyIndex, double duration);

		/**
		 * Calculates an orthonormal basis for the contact point, based on
		 * the primary friction direction (for anisotropic friction) or
		 * a random orientation (for isotropic friction).
		 */
		void calculateContactBasis();

		/**
		 * Applies an impulse to the given body, returning the
		 * change in velocities.
		 */
		void applyImpulse(const Vector3& impulse, RigidBody* body,
			Vector3* velocityChange, Vector3* rotationChange);

		/**
		 * Performs an inertia-weighted impulse based resolution of this
		 * contact alone.
		 */
		void applyVelocityChange(Vector3 velocityChange[2],
			Vector3 rotationChange[2]);

		/**
		 * Performs an inertia weighted penetration resolution of this
		 * contact alone.
		 */
		void applyPositionChange(Vector3 linearChange[2],
			Vector3 angularChange[2],
			double penetration);

		/**
		 * Calculates the impulse needed to resolve this contact,
		 * given that the contact has no friction. A pair of inertia
		 * tensors - one for each contact object - is specified to
		 * save calculation time: the calling function has access to
		 * these anyway.
		 */
		Vector3 calculateFrictionlessImpulse(Matrix3* inverseInertiaTensor);

		/**
		 * Calculates the impulse needed to resolve this contact,
		 * given that the contact has a non-zero coefficient of
		 * friction. A pair of inertia tensors - one for each contact
		 * object - is specified to save calculation time: the calling
		 * function has access to these anyway.
		 */
		Vector3 calculateFrictionImpulse(Matrix3* inverseInertiaTensor);
	};
}