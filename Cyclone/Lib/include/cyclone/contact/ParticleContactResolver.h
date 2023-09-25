#pragma once


namespace cyclone
{
	class ParticleContact;

	/**
	 * The contact resolution routine for particle contacts. One
	 * resolver instance can be shared for the whole simulation.
	 */
	class ParticleContactResolver
	{
	protected:
		/**
		 * Holds the number of iterations allowed.
		 */
		unsigned iterations = 0;

		/**
		 * This is a performance tracking value - we keep a record
		 * of the actual number of iterations used.
		 */
		unsigned iterationsUsed = 0;

	public:
		/**
		 * Creates a new contact resolver.
		 */
		ParticleContactResolver(unsigned iterations);

		/**
		 * Sets the number of iterations that can be used.
		 */
		void setIterations(unsigned iterations);

		/**
		 * Resolves a set of particle contacts for both penetration
		 * and velocity.
		 *
		 * Contacts that cannot interact with each other should be
		 * passed to separate calls to resolveContacts, as the
		 * resolution algorithm takes much longer for lots of contacts
		 * than it does for the same number of contacts in small sets.
		 *
		 * @param contactArray Pointer to an array of particle contact
		 * objects.
		 *
		 * @param numContacts The number of contacts in the array to
		 * resolve.
		 *
		 * @param numIterations The number of iterations through the
		 * resolution algorithm. This should be at least the number of
		 * contacts (otherwise some constraints will not be resolved -
		 * although sometimes this is not noticable). If the
		 * iterations are not needed they will not be used, so adding
		 * more iterations may not make any difference. But in some
		 * cases you would need millions of iterations. Think about
		 * the number of iterations as a bound: if you specify a large
		 * number, sometimes the algorithm WILL use it, and you may
		 * drop frames.
		 *
		 * @param duration The duration of the previous integration step.
		 * This is used to compensate for forces applied.
		*/
		void resolveContacts(ParticleContact* contactArray,
			unsigned numContacts,
			double duration);
	};
}